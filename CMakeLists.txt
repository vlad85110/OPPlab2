cmake_minimum_required(VERSION 3.21)
project(OPPlab1)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "-fopenmp")

#add_executable(OPPlab1 "Not parallel/main.cpp" "Not parallel/SquareMatrix.cpp" "Not parallel/SquareMatrix.h" "Not parallel/Vector.cpp" "Not parallel/Vector.h" "Not parallel/SimpleIterationMethod.h" "Not parallel/Scenarios.h")

add_executable(OPPlab1 "PragmaOmpFor/main.cpp" "PragmaOmpFor/SquareMatrix.cpp" "PragmaOmpFor/SquareMatrix.h" "PragmaOmpFor/Vector.cpp" "PragmaOmpFor/Vector.h" "PragmaOmpFor/SimpleIterationMethod.h" "PragmaOmpFor/Scenarios.h")

#add_executable(OPPlab1 "PragmaOmp/main.cpp" "PragmaOmp/SquareMatrix.cpp" "PragmaOmp/SquareMatrix.h" "PragmaOmp/Vector.cpp" "PragmaOmp/Vector.h" "PragmaOmp/SimpleIterationMethod.h" "PragmaOmp/Scenarios.h")
