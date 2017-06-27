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

#include <iostream>
#include <cmath>
#include "error_defs.hpp"
#include "model.hpp"

using namespace std;
/**
 * Computes the bearing angle (North is 0)
 * @param theta
 * @param start
 * @param end
 * @return
 */
int CModel_Data::ComputeThetaAngle(double *theta, BoardPosition start, BoardPosition end){

	if ((end.row_pos == start.row_pos) && (end.col_pos == start.col_pos))
		return MODEL_ERROR;		// atan2 will fail here - div by zero

	*theta = atan2(end.col_pos - start.col_pos, end.row_pos - start.row_pos);
	*theta = RAD2DEG * (*theta);		//convert to degrees
	return SUCCESS_OK;
}




