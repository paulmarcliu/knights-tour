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

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include "model.hpp"

class CKnight_Controller
{
private:
	CModel_Data *data;

public:
	/**
	 *
	 * @param in
	 */
	CKnight_Controller(CModel_Data *in);
	/**
	 * Will search all paths from start to end
	 *
	 * @param start
	 * @param end
	 * @return
	 */
	int MakeMove(BoardPosition start, BoardPosition end);
	/**
	 * Will check whether this is a valid move
	 * @param start
	 * @param end
	 * @return
	 */
	int IsValidKnightMove(BoardPosition start, BoardPosition end);
	/**
	 *
	 * @param index
	 * @param start
	 * @param next
	 * @return
	 */
	int GetNextPositionAtIndex(int index, BoardPosition start, BoardPosition *next);
	// visited?
	/**
	 *
	 * @param index
	 * @param start
	 * @return
	 */
	BoardPosition GetRawNextPositionFromIndex(int index, BoardPosition start);
	/**
	 *
	 * @param start
	 * @param end
	 * @param next
	 * @return
	 */
	int ComputeMoveFromDistance(BoardPosition start, BoardPosition end, BoardPosition *next);
	/**
	 *
	 */
	void ClearMatrices(void){
		data->ClearMatrices();
	}
	/**
	 *
	 * @param in
	 * @param value
	 * @return
	 */
	int Set_At(BoardPosition in, char value){
		return data->Set_At(in, value);
	}

	// Compute direction index
	/**
	 *
	 * @param start
	 * @param end
	 * @param next
	 * @return
	 */
	int ComputeDirectionIndex(BoardPosition start, BoardPosition end, BoardPosition *next);

	/**
	 *
	 * @param end
	 */
	void ComputeEndMoves(BoardPosition end){
		data->ComputeEndMoves(end);
	}

	/**
	 *
	 * @return
	 */
	int Max_Rows(void){return data->Max_Rows();}

	/**
	 *
	 * @return
	 */
	int Max_Cols(void){return data->Max_Cols();}

};



#endif /* CONTROLLER_HPP_ */
