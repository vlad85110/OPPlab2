#pragma once

#include <ctime>
#include <cstdio>
#include <iostream>
#include <mpi.h>

#include "SquareMatrix.h"
#include "Vector.h"
#include "schedule.h"

bool terminationCriterion(_Matrix* matrixA, _Vector* vectorB, _Vector* vectorX, double eps, int size);

void Iteration(_Matrix* matrixA, _Vector* vectorB, _Vector* vectorX, double t, const double eps, int size) {
    int rank, mpi_size;

    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    struct timespec start{}, end{};

    clock_gettime(CLOCK_REALTIME, &start);

    _Vector *tmp1;
    _Vector *tmp2;
    _Vector *ptr;

    do {
        tmp1 = Matrix::multiply(matrixA, vectorX); //1

        tmp2 = Vector::minus(tmp1, vectorB);//2
        Vector::free(tmp1);

        tmp1 = Vector::multiply(tmp2, t);//3

        Vector::free(tmp2);

        ptr = schedule::send_vector(vectorX);

        tmp2 = Vector::minus(ptr, tmp1);//4
        Vector::free(tmp1);
        Vector::free(vectorX);

        vectorX = schedule::join_vector(tmp2, size);

        Vector::free(tmp2);

    } while (!terminationCriterion(matrixA, vectorB, vectorX, eps, size));



    clock_gettime(CLOCK_REALTIME, &end);
    if (rank == 0) {
        printf("Time taken: %lf sec.\n",
               (double) (end.tv_sec - start.tv_sec)
               + 0.000000001 * (double) (end.tv_nsec - start.tv_nsec));
    }
}

bool terminationCriterion(_Matrix* matrixA, _Vector* vectorB, _Vector* vectorX, const double eps, int size) {
    int rank, mpi_size;

    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    auto chunk = schedule::get_chunk(size, mpi_size);

    static int cnt = 1;
    double mes;

    _Vector* tmp1;
    _Vector* tmp2;

    double  tmp_mes1, tmp_mes2;

    tmp1 = Matrix::multiply(matrixA,vectorX);

    tmp2 = Vector::minus(tmp1, vectorB);
    Vector::free(tmp1);

    tmp_mes1 = Vector::measure(tmp2, chunk);
    tmp_mes2 = Vector::measure(vectorB, chunk);

    mes = tmp_mes1 / tmp_mes2;

    MPI_Bcast(&mes, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        //std::cerr << mes << std::endl;
    }

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