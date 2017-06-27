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

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "constants.hpp"
#include "error_defs.hpp"
#include <vector>
#include <cmath>

typedef struct
{
	int row_pos;
	int col_pos;
}BoardPosition;

class CModel_Data
{
private:
	char board_matrix[MAX_ROWS][MAX_COLS];
	char end_board_matrix[MAX_ROWS][MAX_COLS];
	std::vector <BoardPosition> end_list;
public:
	CModel_Data(){ClearMatrices();}
	/**
	 * Clears the board matrix and end_board_matrix - do this at initialization
	 */
	void ClearMatrices(void){
		for (int i = 0; i < MAX_ROWS; i++){
			for (int j = 0; j < MAX_COLS; j++){
				board_matrix[i][j] = end_board_matrix[i][j] = ' ';
			}
		}
		end_list.clear();		// clear list
	}
	/**
	 *
	 * Return the maximum number of rows in the matrix
	 * @return
	 */
	int Max_Rows(){return MAX_ROWS;}
	/**
	 * Returns the maximum number of columns in the matrix
	 */
	int Max_Cols(){return MAX_COLS;}
	/**
	 * @param in
	 * @return - returns SUCCESS_OK if the position is within the matrix
	 */
	int IsPositionValid(BoardPosition in){
		if ((in.row_pos < 0) || (in.col_pos < 0) || (in.row_pos >= MAX_ROWS) || (in.col_pos >= MAX_COLS)) {
			return MODEL_ERROR;
		}
		return SUCCESS_OK;
	}
	/**
	 * Returns SUCCESS_OK if board position 'in' can be set with value
	 * @param in
	 * @param value
	 * @return
	 */
	int Set_At(BoardPosition in, char value){
		if (IsPositionValid(in) != SUCCESS_OK){
			return MODEL_ERROR;
		}
		board_matrix[in.row_pos][in.col_pos] = value;
		return SUCCESS_OK;
	}
	/**
	 * Returns SUCCESS_OK if the board position 'in' contains value
	 * @param in
	 * @param value
	 * @return
	 */
	int Get_At(BoardPosition in, char *value){
		if (IsPositionValid(in) != SUCCESS_OK){
			return MODEL_ERROR;
		}
		*value = board_matrix[in.row_pos][in.col_pos];
		return SUCCESS_OK;
	}
	/**
	 * Returns SUCCESS_OK if a == b
	 * @param a
	 * @param b
	 * @return
	 */
	int ArePositionsEqual(BoardPosition a, BoardPosition b){
		if ((a.row_pos == b.row_pos) && (a.col_pos == b.col_pos))
			return SUCCESS_OK;
		return MODEL_ERROR;
	}
	/**
	 * Return SUCCESS_OK if the board position 'in' has not been visited before
	 * @param in
	 * @return
	 */
	int IsPositionNotVisited(BoardPosition in){
		char value;
		if (Get_At(in, &value) != SUCCESS_OK){
			return MODEL_ERROR;
		}
		if (value == ' '){
			return SUCCESS_OK;
		}
		return MODEL_ERROR;
	}
	/**
	 * Returns SUCCESS_OK if "in" is equal to the position shown by 'E'
	 * @param in
	 * @return
	 */
	int IsPositionTheEnd(BoardPosition in){
		char value;
		if ((Get_At(in, &value) != SUCCESS_OK))
			return MODEL_ERROR;
		if (value == 'E') return SUCCESS_OK;
		return MODEL_ERROR;
	}
	/**
	 * Compute the physical distance between a and b
	 * @param a
	 * @param b
	 * @return distance
	 */
	double ComputeDistance(BoardPosition a, BoardPosition b){
		return sqrt(pow(a.row_pos - b.row_pos, 2.0) + pow(a.col_pos - b.col_pos, 2.0));
	}
	/**
	 *  Will set the possible board moves and put in endlist
	 */
	void ComputeEndMoves(BoardPosition end){
		BoardPosition temp;
		for (int i = 0; i < 8; i++){
			switch (i){
			case 0:	temp.row_pos = end.row_pos-2; temp.col_pos = end.col_pos+1;	break;
			case 1:	temp.row_pos = end.row_pos-1; temp.col_pos = end.col_pos+2;	break;
			case 2:	temp.row_pos = end.row_pos+1; temp.col_pos = end.col_pos+2;	break;
			case 3:	temp.row_pos = end.row_pos+2; temp.col_pos = end.col_pos+1;	break;
			case 4:	temp.row_pos = end.row_pos+2; temp.col_pos = end.col_pos-1;	break;
			case 5:	temp.row_pos = end.row_pos+1; temp.col_pos = end.col_pos-2;	break;
			case 6:	temp.row_pos = end.row_pos-1; temp.col_pos = end.col_pos-2;	break;
			default:temp.row_pos = end.row_pos-2; temp.col_pos = end.col_pos-1;	break;
			}
			if ((IsPositionValid(temp) == SUCCESS_OK) && (IsPositionNotVisited(temp) == SUCCESS_OK)){
				end_list.push_back(temp);
				end_board_matrix[temp.row_pos][temp.col_pos] = 'X';
			}
		}
	}

	/**
	 * Will set the possible board moves and put in the list passed in
	 * @param in
	 * @param plist
	 */
	void ComputePossibleMovesList(BoardPosition in, std::vector <BoardPosition> *plist){
		BoardPosition temp;
		for (int i = 0; i < 8; i++){
			switch (i){
			case 0:	temp.row_pos = in.row_pos-2; temp.col_pos = in.col_pos+1;	break;
			case 1:	temp.row_pos = in.row_pos-1; temp.col_pos = in.col_pos+2;	break;
			case 2:	temp.row_pos = in.row_pos+1; temp.col_pos = in.col_pos+2;	break;
			case 3:	temp.row_pos = in.row_pos+2; temp.col_pos = in.col_pos+1;	break;
			case 4:	temp.row_pos = in.row_pos+2; temp.col_pos = in.col_pos-1;	break;
			case 5:	temp.row_pos = in.row_pos+1; temp.col_pos = in.col_pos-2;	break;
			case 6:	temp.row_pos = in.row_pos-1; temp.col_pos = in.col_pos-2;	break;
			default:temp.row_pos = in.row_pos-2; temp.col_pos = in.col_pos-1;	break;
			}
			if (((IsPositionValid(temp) == SUCCESS_OK) && (IsPositionNotVisited(temp) == SUCCESS_OK))
					|| (IsPositionTheEnd(temp) == SUCCESS_OK)){
				plist->push_back(temp);
			}
		}
	}
	/**
	 * GetEndListSize - return the number of entries in the end move list.
	 * @return - number of possible moves
	 */
	int GetEndListSize(void){
		return end_list.size();
	}
	/**
	 * Will return the position value pointed by the index in.
	 * @param in
	 * @return BoardPosition value
	 */
	BoardPosition GetPositionFromEndList(int in){
		return end_list[in];
	}

	int ComputeThetaAngle(double *theta, BoardPosition start, BoardPosition end);

};



#endif /* MODEL_HPP_ */
