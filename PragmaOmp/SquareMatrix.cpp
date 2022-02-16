#include "SquareMatrix.h"
#include <iostream>


SquareMatrix::SquareMatrix(size_t size) : data(size * size){
    this->size = size;
}

void SquareMatrix::init() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j)
                data[i * size + j] = 2;
            else
                data[i * size + j] = 1;
        }
    }
}

Vector SquareMatrix::operator*(Vector &vector) const {
    Vector result(size, 0);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
           result.data[i] += data[size * i + j] * vector[j];
        }
    }
    return result;
}

[[maybe_unused]] void SquareMatrix::print() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << data[size * i + j] << " ";
        }
        std::cout << "\n";
    }
}

double SquareMatrix::operator[](const int index) const {
    return data[index];
}