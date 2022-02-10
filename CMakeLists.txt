cmake_minimum_required(VERSION 3.21)
project(OPPlab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(OPPlab1 main.cpp SquareMatrix.cpp SquareMatrix.h Vector.cpp Vector.h Matrix.cpp Matrix.h SimpleIterationMethod.h)
