cmake_minimum_required(VERSION 3.6)
project(OPPlab1)

set(CMAKE_CXX_STANDARD 17)

#include(/usr/lib/x86_64-linux-gnu/mpich)


set(CMAKE_C_COMPILER «/usr/bin/mpicc»)
set(CMAKE_CXX_COMPILER "/usr/bin/mpicxx.mpich")

#add_executable(OPPlab1 "Not parallel/main.cpp" "Not parallel/SquareMatrix.cpp" "Not parallel/SquareMatrix.h" "Not parallel/Vector.cpp" "Not parallel/Vector.h" "Not parallel/SimpleIterationMethod.h" "Not parallel/Scenarios.h")

#add_executable(OPPlab1 "PragmaOmpFor/main.cpp" "PragmaOmpFor/SquareMatrix.cpp" "PragmaOmpFor/SquareMatrix.h" "PragmaOmpFor/Vector.cpp" "PragmaOmpFor/Vector.h" "PragmaOmpFor/SimpleIterationMethod.h" "PragmaOmpFor/Scenarios.h" PragmaOmpFor/reduction.h)

add_executable(OPPlab1 "MPI/main.cpp" "MPI/SquareMatrix.cpp" "MPI/SquareMatrix.h" "MPI/Vector.cpp" "MPI/Vector.h" "MPI/SimpleIterationMethod.h" "MPI/Scenarios.h" MPI/schedule.h)
