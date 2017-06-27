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

#include <model.hpp>
#include "gtest/gtest.h"
#include "constants.hpp"
#include "error_defs.hpp"
#include "model.hpp"


// To use a test fixture, derive a class from testing::Test.
class CModel_DataTest : public testing::Test {
private:
	CModel_Data test;
protected:  // You should make the members protected s.t. they can be
             // accessed from sub-classes.

  	// virtual void SetUp() will be called before each test is run.  You
  	// should define it if you need to initialize the varaibles.
  	// Otherwise, this can be skipped.
  	virtual void SetUp() {
  	}

  	// virtual void TearDown() will be called after each test is run.
  	// You should define it if there is cleanup work to do.  Otherwise,
  	// you don't have to provide it.
  	//
   	virtual void TearDown() {
   	}
public:
   	void CheckMatrixLimitsTest(void){
   		ASSERT_EQ(test.Max_Rows(), MAX_ROWS);
   		ASSERT_EQ(test.Max_Cols(), MAX_COLS);
   	}

   	void IsPositionValidTest(){
   		BoardPosition in;
   		in.row_pos = -1;   		in.col_pos = -1;
		ASSERT_NE(test.IsPositionValid(in), SUCCESS_OK);
   	}

	void TestSetAndGet(void) {
		BoardPosition in;
		int i, j;
		char k, k_in;
		for (k = 'A'; k <= 'Z'; k++) {
			for (i = 0; i < MAX_ROWS; i++) {
				for (j = 0; j < MAX_COLS; j++) {
					in.row_pos = i;
					in.col_pos = j;
					ASSERT_EQ(test.Set_At(in, k), SUCCESS_OK);
					ASSERT_EQ(test.Get_At(in, &k_in), SUCCESS_OK);
					ASSERT_EQ(k_in, k);
				}
			}
		}
	}

	void TestClearMatrices(void){
		char k_in;
		BoardPosition in;
		test.ClearMatrices();
		for (int i = 0; i < MAX_ROWS; i++) {
			for (int j = 0; j < MAX_COLS; j++) {
				in.row_pos = i; in.col_pos = j;
				ASSERT_EQ(test.Get_At(in, &k_in), SUCCESS_OK);
				ASSERT_EQ(k_in, ' ');
			}
		}
	}
	void TestArePositionsEqual(void){
		BoardPosition a, b;
		a.row_pos = b.row_pos = 0;
		a.col_pos = b.col_pos = 0;
		ASSERT_EQ(test.ArePositionsEqual(a, b), SUCCESS_OK);
	}

	void TestIsPositionNotVisited(void) {
		char k_in;
		BoardPosition in;
		test.ClearMatrices();
		for (int i = 0; i < MAX_ROWS; i++) {
			for (int j = 0; j < MAX_COLS; j++) {
				in.row_pos = i; in.col_pos = j;
				ASSERT_EQ(test.Get_At(in, &k_in), SUCCESS_OK);
				ASSERT_EQ(k_in, ' ');
			}
		}
	}

	void TestIsPositionTheEnd(void){
		BoardPosition in;
        in.row_pos = in.col_pos = 0;
        ASSERT_EQ(test.Set_At(in, 'E'), SUCCESS_OK);
        ASSERT_EQ(test.IsPositionTheEnd(in), SUCCESS_OK);
	}

    void TestComputeDistance(void) {
        BoardPosition a, b;
        a.row_pos = a.col_pos = 0;
        b.row_pos = b.col_pos = 2;
        ASSERT_DOUBLE_EQ(test.ComputeDistance(a, b), 2.8284271247461903);
    }

    void ComputeEndMoves(BoardPosition end) {
    }

    void ComputePossibleMovesList(BoardPosition in, std::vector <BoardPosition> *plist) {
    }

    int ComputeThetaAngle(double *theta, BoardPosition start, BoardPosition end) {
    }
    int GetEndListSize(void) {
    }
    BoardPosition GetPositionFromEndList(int in) {
    }
 };

TEST_F(CModel_DataTest, CheckMatrixLimitsTest) {
	CheckMatrixLimitsTest();
}

TEST_F(CModel_DataTest, IsPositionValidTest) {
	IsPositionValidTest();
}

TEST_F(CModel_DataTest, TestSetAndGet) {
	TestSetAndGet();
}

TEST_F(CModel_DataTest, TestClearMatrices) {
	TestClearMatrices();
}

TEST_F(CModel_DataTest, TestArePositionsEqual) {
	TestArePositionsEqual();
}

TEST_F(CModel_DataTest, TestIsPositionNotVisited) {
	TestIsPositionNotVisited();
}

TEST_F(CModel_DataTest, TestIsPositionTheEnd) {
    TestIsPositionTheEnd();
}

TEST_F(CModel_DataTest, TestComputeDistance) {
    TestComputeDistance();
}
