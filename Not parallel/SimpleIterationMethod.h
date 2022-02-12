#pragma once

#include "SquareMatrix.h"
#include "Vector.h"
#include <ctime>
#include <cstdio>



bool terminationCriterion(SquareMatrix &matrixA, Vector &vectorB, Vector &vectorX, double eps);

Vector& Iteration(SquareMatrix &matrixA, Vector &vectorB, Vector &vectorX, double t, const double eps) {
    struct timespec start{}, end{};

    clock_gettime(CLOCK_REALTIME, &start);
    while (!terminationCriterion(matrixA, vectorB, vectorX, eps)) {
        vectorX = vectorX - (matrixA * vectorX - vectorB) * t;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf("Time taken: %lf sec.\n",
           (double)(end.tv_sec-start.tv_sec)
           + 0.000000001*(double)(end.tv_nsec-start.tv_nsec));

    return vectorX;
}

bool terminationCriterion(SquareMatrix &matrixA, Vector &vectorB, Vector &vectorX, const double eps) {
    static int cnt = 1;
    double mes = ((matrixA * vectorX - vectorB).measure() / vectorB.measure());

    if (cnt == 1) {
        cnt++;
        return false;
    }

    if (mes < eps) {
        cnt++;
        return true;
    }
    cnt++;

    return false;
}