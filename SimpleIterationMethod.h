#pragma once

#include "Matrix.h"

//using MatrixPtr = std::shared_ptr<Matrix>;

MatrixPtr Iteration(MatrixPtr &matrixA, MatrixPtr &vectorB, MatrixPtr &vectorX) {
    double t, eps;

    vectorX = vectorX - (*(*matrixA * vectorX) * t);
}