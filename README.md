Knight Tour Project

The purpose of this project is to investigate various algorithms related to the
knight's tour.

This is a project that appeared interesting and related to path optimization -
which is of particular interest to me.

I used an MVC design pattern in order for me to update in the future. I have started
a unit test skeleton using GoogleTest.  If you don't use GoogleTest, please comment
the relevant portions in the CMakeList.txt

The first checkin covers an implementation of least cost distance to destination and
Warnsdorff's algorithm.  This implementation covers all possible start to end positions.

My next checkin will be to include obstacles (in Model) and include neural networks / Machine Learning (in Controller)  to compute optimal paths esp. in obstructed environments.

How to build:
1.  cd ~/knight
2.  mkdir build
3.  cd build
4.  cmake ..
5.  cmake --build .




