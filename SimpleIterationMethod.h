#pragma once

#include "SquareMatrix.h"
#include "Vector.h"

bool terminationCriterion(SquareMatrix &matrixA, Vector &vectorB, Vector &vectorX);

Vector& Iteration(SquareMatrix &matrixA, Vector &vectorB, Vector &vectorX) {
    double t = 0.01;

    while (!terminationCriterion(matrixA, vectorB, vectorX)) {
        vectorX = vectorX - (matrixA * vectorX - vectorB) * t;
    }
    return vectorX;
}

bool terminationCriterion(SquareMatrix &matrixA, Vector &vectorB, Vector &vectorX) {
    static int cnt = 1;
    static const double eps = 0.00005;

    if (cnt == 1) {
        cnt++;
        return false;
    }

    if (((matrixA * vectorX - vectorB).measure() / vectorB.measure()) < eps) {
        cnt++;
        return true;
    }

    return false;
}