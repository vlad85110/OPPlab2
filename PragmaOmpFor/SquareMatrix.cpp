#include "SquareMatrix.h"
#include <iostream>
#include <omp.h>


const int threads = omp_get_num_threads();

SquareMatrix::SquareMatrix(size_t size) : data(size * size){
    this->size = size;
}

void SquareMatrix::init() {
    #pragma omp parallel for schedule (static, CHUNK_SIZE)
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
    auto array = vector.getVector();

    #pragma omp parallel for schedule (static, CHUNK_SIZE)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result.data[i] += data[size * i + j] * array[j];
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
