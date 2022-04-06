#pragma once

#include <iostream>
#include "SimpleIterationMethod.h"


namespace Scenarios {

    void givenSolution(int size) {
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        _Matrix *matrix = nullptr;
        _Vector *vectorB = nullptr;
        if (rank == 0) {
            matrix = Matrix::create(size, 2);
            vectorB = Vector::create(size, size + 1);
            Matrix::init(matrix);
        }
        matrix = schedule::send_matrix(matrix);
        _Vector *vectorB_c = schedule::send_vector(vectorB);
        _Vector *vectorX = Vector::create(size);

        Iteration(matrix, vectorB_c, vectorX, 0.0009, 0.0000005, size);

        if (vectorB != nullptr) {
            Vector::free(vectorB);
        } else {
            Vector::free(vectorB_c);
        }
        Vector::free(vectorX);
        Matrix::free(matrix);
    }

    void arbitraryDecision(int size) {
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        _Matrix *matrix = nullptr;
        _Vector *vectorB;
        _Vector* vectorU;
        if (rank == 0) {
            matrix = Matrix::create(size, 2);
            Matrix::init(matrix);
        }
        matrix = schedule::send_matrix(matrix);

        vectorU = Vector::create(size);
        Vector::initWithSinus(vectorU);

        _Vector* vectorX = Vector::create(size);

        vectorB = Matrix::multiply(matrix, vectorU);

        Iteration(matrix, vectorB, vectorX, 0.001, 0.00005, size);

        if (vectorB != nullptr) {
            Vector::free(vectorB);
        }
        Vector::free(vectorX);

        if (vectorU != nullptr) {
            Vector::free(vectorU);
        }

        Matrix::free(matrix);

    }
}