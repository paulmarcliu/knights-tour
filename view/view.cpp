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
#include "view.hpp"
#include "constants.hpp"
#include "model.hpp"
#include "error_defs.hpp"

using namespace std;

/**
 * @function
 * @ Description
 * Will display the board.
 */
void CView_Data::UpdateDisplay(void)
{
	int i, j;
	for (i = 0; i < data->Max_Rows(); i++)
	{
		if (i == 0)
		{
			cout << "\n  ";
			for (j = 0; j < data->Max_Cols(); j++)
			{
				cout << (j%10) << ",";
			}
			cout << "\n";
		}
		for (j = 0; j < data->Max_Cols(); j++)
		{
			if (j == 0)
			{
				cout << (i%10) << ":";
			}
			char value;
			BoardPosition pos;
			pos.row_pos = i; pos.col_pos = j;
			data->Get_At(pos, &value);
			cout << value << ",";
		}
		cout << "\n";
	}

}



