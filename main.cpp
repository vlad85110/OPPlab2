#include <iostream>
#include "Matrix.h"
#include "SquareMatrix.h"
#include "Vector.h"

using V = std::vector<double>;

int main() {
    Matrix * matrix = new SquareMatrix(3);
    matrix->init();
    matrix->print();

    Matrix * vector = new Vector(3, 1);

    *vector * 2;
    std::cout << vector->measure() << std::endl;
    vector->print();

    return 0;
}
