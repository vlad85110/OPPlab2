#pragma once

#include "SimpleIterationMethod.h"
#include "SquareMatrix.h"
#include "Vector.h"

#include <iostream>

namespace Scenarios {

    void givenSolution(int size) {
        SquareMatrix matrix(size);
        Vector vectorX(size);
        Vector vectorB(size, size + 1);
        Vector expected(size, 1);

        matrix.init();
        std::cout << "*Given Solution scenario*" << std::endl;

        Vector result(Iteration(matrix, vectorB, vectorX, 0.0009, 0.0000005));

        if (size <= 5) {
            std::cout << "Result vector: " << std::endl;
            result.print();

            std::cout << "Expected Result: " << std::endl;

            expected.print();
        }
            std::cout << "Error: " << std::endl;
            std::cout << (expected - result).max() << std::endl;

        std::cout << "------------------------" << std::endl;
    }

    void arbitraryDecision(int size) {
        SquareMatrix matrix(size);
        Vector vectorX(size);
        Vector vectorU(size);
        vectorU.initWithSinus(size);

        matrix.init();
        Vector vectorB(matrix * vectorU);

        std::cout << "*Arbitrary Decision scenario*" << std::endl;
        Vector result(Iteration(matrix, vectorB, vectorX, 0.001, 0.00005));

        if (size <= 5) {
            std::cout << "Result vector: " << std::endl;
            result.print();

            std::cout << "Expected Result: " << std::endl;
            vectorU.print();

            std::cout << "Error: " << std::endl;
            std::cout << (vectorU - result).max() << std::endl;
        }

        std::cout << "------------------------" << std::endl;
    }

    /*void heatDistribution() {}*/

}