/*
The MIT License (MIT)

Copyright (c) 2017 Paul Marc Liu

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "constants.hpp"
#include "error_defs.hpp"
#include "controller.hpp"
#include "model.hpp"
#include <stdlib.h>
#include <iostream>
#include <cmath>


#define CONTROLLER_DEBUG 0
using namespace std;
/**
 *
 * @param in
 */
CKnight_Controller::CKnight_Controller(CModel_Data *in)
{
	data = in;
}

/**
 * GetNextPositionAtIndex - will return the next board position based on index and if not visited
 * @param index
 * @param start
 * @param next
 * @return
 */
int CKnight_Controller::GetNextPositionAtIndex(int index, BoardPosition start, BoardPosition *next)
{
#if CONTROLLER_DEBUG	// for future neural network use
	BoardPosition temp = GetRawNextPositionFromIndex(index, start);
	while (IsValidKnightMove(start, temp) != SUCCESS_OK)
	{
		cout << "Invalid move from " << start.row_pos << "," << start.col_pos << " to " << temp.row_pos << ","
				<< temp.col_pos << "Index =" << index << endl;
		index++;
		if (index >=8)
			index = index - 8;
		temp = GetRawNextPositionFromIndex(index, start);
	}

	if ( (IsPositionNotVisited(temp) == SUCCESS_OK) || (IsPositionTheEnd(temp) == SUCCESS_OK))
	{
		next->row_pos = temp.row_pos;
		next->col_pos = temp.col_pos;
		return SUCCESS_OK;
	}
#endif
	return CONTROLLER_ERROR;
}


/**
 * Will return the next move that will bring it closer to the end
 * @param start
 * @param end
 * @param next
 * @return SUCCESS_OK or CONTROLLER_ERROR
 */
int CKnight_Controller::ComputeDirectionIndex(BoardPosition start, BoardPosition end, BoardPosition *next)
{
	double theta;
	int index;
	if (data->ComputeThetaAngle(&theta, start, end) != SUCCESS_OK)		// calculate bearing
		return CONTROLLER_ERROR;		// atan2 will fail here - div by zero

	if ((theta > -180.0) && (theta <= -135.0))
		index = 7;
	else if ((theta > -135.0) && (theta <= -90.0))
		index = 6;
	else if ((theta > -90.0) && (theta <= -45.0))
		index = 5;
	else if ((theta > -45.0) && (theta <= 0))
		index = 4;
	else if ((theta >= 0.0) && (theta < 45.0))
		index = 3;
	else if ((theta >= 45.0) && (theta < 90.0))
		index = 2;
	else if ((theta >= 90.0) && (theta < 135.0))
		index = 1;
	else
		index = 0;

	if (GetNextPositionAtIndex(index, start, next) == SUCCESS_OK)
	{
		return SUCCESS_OK;
	}
	return CONTROLLER_ERROR;
}

/**
 * Compute the next move based on start and end position
 * @param start
 * @param end
 * @param next
 * @return
 */
int CKnight_Controller::ComputeMoveFromDistance(BoardPosition start, BoardPosition end, BoardPosition *next){
	std::vector <BoardPosition> pos_list;		// needed to make the list
	BoardPosition temp, end_temp;
	double distance, temp_distance;

	pos_list.clear();	// empty list

	data->ComputePossibleMovesList(start, &pos_list);	// create list
	if (pos_list.size() > 0){
		temp.row_pos = pos_list[0].row_pos;
		temp.col_pos = pos_list[0].col_pos;
		temp_distance = data->ComputeDistance(pos_list[0], end);
		for (size_t i = 1; i < pos_list.size(); i++){
			distance = data->ComputeDistance(pos_list[i], end);
			if (temp_distance > distance){
				temp.row_pos = pos_list[i].row_pos;
				temp.col_pos = pos_list[i].col_pos;
				temp_distance = distance;
			}
		}  // for

		if (temp_distance < 3){
			for (size_t p = 0; p < pos_list.size(); p++){
				for (int k = 0; k < data->GetEndListSize(); k++){
					end_temp = data->GetPositionFromEndList(k);
					if (data->ArePositionsEqual(pos_list[p], end_temp) == SUCCESS_OK){
						next->row_pos = end_temp.row_pos; next->col_pos = end_temp.col_pos;
						return SUCCESS_OK;	// found next
					}
				}
#if CONTROLLER_DEBUG				
				cout << "nextMoveList-" << p << ":" << pos_list[p].row_pos << "," << pos_list[p].col_pos << endl;
#endif
			}
		}

		next->row_pos = temp.row_pos; next->col_pos = temp.col_pos;

		return SUCCESS_OK;
	}
	return CONTROLLER_ERROR;
}

/**
 *
 * @param start
 * @param end
 * @return
 */
int CKnight_Controller::MakeMove(BoardPosition start, BoardPosition end)
{
	BoardPosition next;
	int return_value = 0;

	if ( data->ArePositionsEqual(start, end) == SUCCESS_OK)	// reached end
	{
		return 1;
	}
	else
	{
		if (data->IsPositionNotVisited(start) == SUCCESS_OK)
		{
			data->Set_At(start, 'K');
		}
		if (ComputeMoveFromDistance(start, end, &next) == SUCCESS_OK)
		{
#if CONTROLLER_DEBUG	
			cout << "+ move from " << start.row_pos << "," << start.col_pos
						<< " to " << next.row_pos << "," << next.col_pos << "\n";
#endif
			return_value = MakeMove(next, end);
		}
#if CONTROLLER_DEBUG
		else
		{
			cout << "- move from " << start.row_pos << "," << start.col_pos
						<< " to " << next.row_pos << "," << next.col_pos << "\n";
		}
#endif
	}
	return return_value;
}

/**
 *
 * @param start
 * @param end
 * @return
 */
int CKnight_Controller::IsValidKnightMove(BoardPosition start, BoardPosition end)
{
	// The knight can move in an L shape of 2 x 1 squares.
	int count = 0;

	if ((data->IsPositionValid(start) != SUCCESS_OK) ||(data->IsPositionValid(end) != SUCCESS_OK))
	{
		return CONTROLLER_ERROR;
	}

	for (count = 0; count < 8; count++)
	{
		switch (count)
		{
		case 0:
			if ((end.row_pos == start.row_pos-2) && (end.col_pos == start.col_pos+1))
				return SUCCESS_OK;
			break;
		case 1:
			if ((end.row_pos == start.row_pos-1) && (end.col_pos == start.col_pos+2))
				return SUCCESS_OK;
			break;
		case 2:
			if ((end.row_pos == start.row_pos+1) && (end.col_pos == start.col_pos+2))
				return SUCCESS_OK;
			break;
		case 3:
			if ((end.row_pos == start.row_pos+2) && (end.col_pos == start.col_pos+1))
				return SUCCESS_OK;
			break;
		case 4:
			if ((end.row_pos == start.row_pos+2) && (end.col_pos == start.col_pos-1))
				return SUCCESS_OK;
			break;
		case 5:
			if ((end.row_pos == start.row_pos+1) && (end.col_pos == start.col_pos-2))
				return SUCCESS_OK;
			break;
		case 6:
			if ((end.row_pos == start.row_pos-1) && (end.col_pos == start.col_pos-2))
				return SUCCESS_OK;
			break;
		case 7:
			if ((end.row_pos == start.row_pos-2) && (end.col_pos == start.col_pos-1))
				return SUCCESS_OK;
			break;
		}
	}
	return CONTROLLER_ERROR;
}



