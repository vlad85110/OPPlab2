#pragma once

#include <iostream>
#include "SimpleIterationMethod.h"


namespace Scenarios {

    void givenSolution(int size) {
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        _Matrix* matrix = nullptr;
        _Vector* vectorB = nullptr;
        if (rank == 0) {
            matrix = Matrix::create(size, 2);
            vectorB = Vector::create(size, size + 1);
            Matrix::init(matrix);
        }
        matrix = schedule::send_matrix(matrix);
        vectorB = schedule::send_vector(vectorB);
        //Vector::print(vectorB);
        _Vector* vectorX = Vector::create(size);

        _Vector* expected = Vector::create(size, 1);

        //std::cout << "*Given Solution scenario*" << std::endl;
        _Vector* result = Iteration(matrix, vectorB, vectorX, 0.0009, 0.0000005, size);

        if (rank == 0) {

            if (size <= 5) {
                std::cout << "Result vector: " << std::endl;
                Vector::print(result);

                std::cout << "Expected Result: " << std::endl;

                Vector::print(expected);

                std::cout << "Error: " << std::endl;
                std::cout << Vector::max_el(Vector::minus(expected, result)) << std::endl;
            }

            std::cout << "------------------------" << std::endl;
        }
    }

    /*void arbitraryDecision(int size) {
        __Matrix matrix = Matrix::create(size);
        _Vector vectorX = Vector::create(size);
        _Vector vectorU = Vector::create(size);
        Vector::initWithSinus(vectorU, size);
        Matrix::init(matrix, size);

        _Vector vectorB = Matrix::multiply(matrix, vectorU, size);

        std::cout << "*Arbitrary Decision scenario*" << std::endl;
        _Vector result = Iteration(matrix, vectorB, vectorX, 0.001, 0.00005, size);

        if (size <= 5) {
            std::cout << "Result vector: " << std::endl;
            Vector::print(result, size);

            std::cout << "Expected Result: " << std::endl;
            Vector::print(vectorU, size);

            std::cout << "Error: " << std::endl;
            std::cout << Vector::max_el(Vector::minus(vectorU, result, size), size) << std::endl;
        }

        std::cout << "------------------------" << std::endl;
    }*/
}