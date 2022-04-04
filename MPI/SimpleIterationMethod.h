#pragma once

#include "SquareMatrix.h"
#include "Vector.h"
#include <ctime>
#include <cstdio>
#include <iostream>


bool terminationCriterion(_Matrix matrixA, _Vector vectorB, _Vector vectorX, double eps, int size);

_Vector Iteration(_Matrix matrixA, _Vector &vectorB, _Vector &vectorX, double t, const double eps, int size) {
    struct timespec start{}, end{};

    clock_gettime(CLOCK_REALTIME, &start);

    while (!terminationCriterion(matrixA, vectorB, vectorX, eps, size)) {
        vectorX = Vector::minus(vectorX,
                                Vector::multiply(Vector::minus(Matrix::multiply(
                                        matrixA,vectorX, size),vectorB, size), t, size),size);
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf("Time taken: %lf sec.\n",
           (double)(end.tv_sec-start.tv_sec)
           + 0.000000001 * (double)(end.tv_nsec-start.tv_nsec));

    return vectorX;
}

bool terminationCriterion(_Vector matrixA, _Vector vectorB, _Vector vectorX, const double eps, int size) {
    static int cnt = 1;
    double mes;
    mes = Vector::measure(Vector::minus(Matrix::multiply(
            matrixA,vectorX, size),vectorB, size), size)
                    / Vector::measure(vectorB, size);

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