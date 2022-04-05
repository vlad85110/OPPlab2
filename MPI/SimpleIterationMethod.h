#pragma once

#include "SquareMatrix.h"
#include "Vector.h"
#include "schedule.h"
#include <ctime>
#include <cstdio>
#include <iostream>


bool terminationCriterion(_Matrix* matrixA, _Vector* vectorB, _Vector* vectorX, double eps, int size);

_Vector* Iteration(_Matrix* matrixA, _Vector* vectorB, _Vector* vectorX, double t, const double eps, int size) {
    int rank, mpi_size;

    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    struct timespec start{}, end{};
    //vectorX = vectorX 4- (matrixA 1* vectorX 2- vectorB) 3* t;

    clock_gettime(CLOCK_REALTIME, &start);

    _Vector* tmp1 = nullptr;
    _Vector* tmp2 = nullptr;
    _Vector* ptr;
    auto chunk = schedule::get_chunk(size, mpi_size);

    do {
        //todo free
        tmp1 = Matrix::multiply(matrixA, vectorX); //1

        ptr = vectorB;
        ptr->vector = vectorB->vector + chunk * rank;

        tmp2 = Vector::minus(tmp1, ptr);//2
        free(tmp1);

        tmp1 = Vector::multiply(tmp2, t);//3
        free(tmp2);

        ptr = vectorX;
        ptr->vector = vectorX->vector + chunk * rank;

        tmp2 = Vector::minus(ptr, tmp1);//4
        free(tmp1);

        //vectorX = schedule::join_vector(tmp2, size);
        free(tmp2);

        //vectorX = Vector::minus(vectorX,
                               // Vector::multiply(Vector::minus(Matrix::multiply(
        //                                        matrixA, vectorX),vectorB, size), t, size),size);
    } while (!terminationCriterion(matrixA, vectorB, vectorX, eps, size));

    clock_gettime(CLOCK_REALTIME, &end);
    printf("Time taken: %lf sec.\n",
           (double)(end.tv_sec-start.tv_sec)
           + 0.000000001 * (double)(end.tv_nsec-start.tv_nsec));

    return vectorX;
}

bool terminationCriterion(_Matrix* matrixA, _Vector* vectorB, _Vector* vectorX, const double eps, int size) {
    static int cnt = 1;
    double mes;
    mes = Vector::measure(Vector::minus(Matrix::multiply(
            matrixA,vectorX),vectorB))
                    / Vector::measure(vectorB);

    std::cerr<< mes << std::endl;

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