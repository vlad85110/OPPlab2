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

        matrix.init();
        Vector result(Iteration(matrix, vectorB, vectorX));

        std::cout << "*givenSolution scenario*" << std::endl;
        std::cout << "Result vector: " << std::endl;
        result.print();

        std::cout << "Expected Result: " << std::endl;
        Vector expected(size, 1);
        expected.print();

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
        Vector result(Iteration(matrix, vectorB, vectorX));

        std::cout << "*arbitraryDecision scenario*" << std::endl;
        std::cout << "Result vector: " << std::endl;
        result.print();

        std::cout << "Expected Result: " << std::endl;
        vectorU.print();

        std::cout << "Error: " << std::endl;
        std::cout << (vectorU - result).max() << std::endl;

        std::cout << "------------------------" << std::endl;
    }

    void heatDistribution() {}

}