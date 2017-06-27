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
#include <vector>
#include "controller.hpp"
#include "model.hpp"
#include "view.hpp"
#include "error_defs.hpp"
#include "constants.hpp"

#define KNIGHT_DEBUG	0	// used for neural networks development

using namespace std;

class CKnight
{
private:
	CModel_Data my_model;

public:
	CKnight_Controller *p_controller;
	CView_Data *p_view;

	CKnight()
	{
		p_controller = new CKnight_Controller(&my_model);
		p_view = new CView_Data(&my_model);
	}

	~CKnight()
	{
		delete p_controller;
		delete p_view;
	}
};

// This is a test path class to simulate
class Test_Path
{
private:
	std::vector<BoardPosition> simulated_path;
public:
	Test_Path(){};
	void AddNextPosition(BoardPosition in){simulated_path.push_back(in);}
	BoardPosition GetNextPosition(int index){return simulated_path[index];}
	BoardPosition GetFirstPosition(void){return simulated_path.front();}
	int NumberPositions(void){return simulated_path.size();}
	void SetTestPath1(void)
	{
		BoardPosition in;
		in.row_pos = 2; in.col_pos = 3; AddNextPosition(in);	//2,3
		in.row_pos = 3; in.col_pos = 5; AddNextPosition(in);	//3,5
		in.row_pos = 5; in.col_pos = 4; AddNextPosition(in);	//5,4
		in.row_pos = 6; in.col_pos = 6; AddNextPosition(in);	//6,6
	}
	void SetTestPath2(void)
	{
		BoardPosition in;
		int start_row = 1;
		int start_col = 31;
		int end_row = 31;
		int end_col = 0;

		in.row_pos = start_row; in.col_pos = start_col; AddNextPosition(in);	// start_row, start_col
		in.row_pos = end_row; in.col_pos = end_col; AddNextPosition(in);	// end_row, end_col
	}
};

#if KNIGHT_DEBUG
int main()
{
	Knight my_knight;
	Test_Path test1;
	int num_items = 0;
	int needComputing = 0;

	test1.SetTestPath1();
	num_items = test1.NumberPositions();

	for (int i = 0; i < num_items; i++)
	{
		if (i == 0)
		{
			my_knight.p_view->MarkPosition(test1.GetFirstPosition(), 'S');
			needComputing = 0;
		}
		else if (i == (num_items -1))	// last step
		{
			my_knight.p_view->MarkPosition(test1.GetNextPosition(i), 'E');
			needComputing = 1;
		}
		else
		{
			my_knight.p_view->MarkPosition(test1.GetNextPosition(i), 'K');
			needComputing = 1;
		}

		if (needComputing != 0)
		{
			if (my_knight.p_controller->IsValidKnightMove(test1.GetNextPosition(i - 1), test1.GetNextPosition(i)) == SUCCESS_OK)
			{
				cout << "Valid move from " << test1.GetNextPosition(i - 1).row_pos << "," << test1.GetNextPosition(i - 1).col_pos
						<< " to " << test1.GetNextPosition(i).row_pos << "," << test1.GetNextPosition(i).col_pos << "\n";
			}
			else
			{
				cout << "Invalid move from " << test1.GetNextPosition(i - 1).row_pos << "," << test1.GetNextPosition(i - 1).col_pos
						<< " to " << test1.GetNextPosition(i).row_pos << "," << test1.GetNextPosition(i).col_pos << "\n";
			}
		}
	}


	my_knight.p_view->UpdateDisplay();

	return 0;
}
#else
int main()
{
	CKnight my_knight;
	Test_Path test1;
	BoardPosition start, end;
	int return_value = 0;
	int i, j, k, l;
	int missed_count = 0;
	int max_rows = my_knight.p_controller->Max_Rows();
	int max_cols = my_knight.p_controller->Max_Cols();

	for (i = 0; i < max_rows; i++){
		for (j = 0; j < max_cols; j++){
			start.row_pos = i; start.col_pos = j;
			for (k = 0; k < max_rows; k++){
				for (l = 0; l < max_cols; l++){
					end.row_pos = k; end.col_pos = l;
					my_knight.p_controller->ClearMatrices();		// clear the move matrix
					my_knight.p_controller->Set_At(start, 'S');
					my_knight.p_controller->Set_At(end, 'E');
					my_knight.p_controller->ComputeEndMoves(end);	// find the end moves matrix

					return_value = my_knight.p_controller->MakeMove(start, end);
					if (return_value == 0){
						missed_count++;
					}

					my_knight.p_view->UpdateDisplay();
				}
			}
		}
	}
	cout << "Missed counts = " << missed_count << endl;
#if KNIGHT_DEBUG
	test1.SetTestPath2();		// only start and end

	my_knight.p_view->MarkPosition(test1.GetFirstPosition(), 'S');
	my_knight.p_view->MarkPosition(test1.GetNextPosition(1), 'E');
	num_items = my_knight.p_controller->MakeMove(test1.GetFirstPosition(), test1.GetNextPosition(1));

	my_knight.p_view->UpdateDisplay();
#endif	// KNIGHT_DEBUG

	return 0;
}
#endif	// KNIGHT_DEBUG
