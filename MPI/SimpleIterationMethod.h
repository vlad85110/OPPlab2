#pragma once

#include <ctime>
#include <cstdio>
#include <iostream>
#include <mpi.h>

#include "SquareMatrix.h"
#include "Vector.h"
#include "schedule.h"



bool terminationCriterion(_Matrix* matrixA, _Vector* vectorB, _Vector* vectorX, double eps, int size);

_Vector* Iteration(_Matrix* matrixA, _Vector* vectorB, _Vector* vectorX, double t, const double eps, int size) {
    int rank, mpi_size;

    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    struct timespec start{}, end{};
    //vectorX = vectorX 4- (matrixA 1* vectorX 2- vectorB) 3* t;

    clock_gettime(CLOCK_REALTIME, &start);

    _Vector *tmp1 = nullptr;
    _Vector *tmp2 = nullptr;
    _Vector *ptr;
    //auto chunk = schedule::get_chunk(size, mpi_size);

    do {
        //todo free
        tmp1 = Matrix::multiply(matrixA, vectorX); //1

        tmp2 = Vector::minus(tmp1, vectorB);//2
        free(tmp1);

        tmp1 = Vector::multiply(tmp2, t);//3

        free(tmp2);

        ptr = schedule::send_vector(vectorX);

        tmp2 = Vector::minus(ptr, tmp1);//4
        free(tmp1);


        vectorX = schedule::join_vector(tmp2, size);
        free(tmp2);


    } while (!terminationCriterion(matrixA, vectorB, vectorX, eps, size));



    clock_gettime(CLOCK_REALTIME, &end);
    if (rank == 0) {
        printf("Time taken: %lf sec.\n",
               (double) (end.tv_sec - start.tv_sec)
               + 0.000000001 * (double) (end.tv_nsec - start.tv_nsec));
    }

    return vectorX;
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
    //((matrixA 1* vectorX -2 vectorB).measure() / vectorB.measure());

    _Vector* ptr;
    double  tmp_mes1, tmp_mes2;

    tmp1 = Matrix::multiply(matrixA,vectorX);//1

   /* for (int i = 0; i < mpi_size; ++i) {
        MPI_Barrier(MPI_COMM_WORLD);
    }

    if (rank == 1) {
        //Matrix::print(matrixA);
        Vector::print(vectorB);
    }*/

    //ptr = schedule::send_vector(vectorB);


    tmp2 = Vector::minus(tmp1, vectorB);//2

    tmp_mes1 = Vector::measure(tmp2, chunk);

    tmp_mes2 = Vector::measure(vectorB, chunk);//111
    mes = tmp_mes1 / tmp_mes2;



    MPI_Bcast(&mes, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    //std::cerr << mes << std::endl;
    //MPI_Barrier(MPI_COMM_WORLD);

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