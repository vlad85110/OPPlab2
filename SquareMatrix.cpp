#include "SquareMatrix.h"
#include "Vector.h"
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
/**/
std::shared_ptr<Matrix> SquareMatrix::operator*(std::shared_ptr<Matrix> vector) {
    auto result = std::make_shared<Vector>(size, 0);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
           result->data[i] += data[size * i + j] * (*vector)[j];
        }
    }
    return result;
}

void SquareMatrix::print() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << data[size * i + j] << " ";
        }
        std::cout << "\n";
    }
}

void SquareMatrix::operator*(double num){
    throw std::runtime_error("We don't need to multiple matrix by number");
}

double SquareMatrix::measure() {
    std::cout << "I don't know" << std::endl;
    return -1;
}

double SquareMatrix::operator[](int index){
    return data[index];
}

SquareMatrix::~SquareMatrix() = default;
