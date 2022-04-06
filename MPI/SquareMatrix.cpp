#include "SquareMatrix.h"
#include "Vector.h"
#include <iostream>

namespace Matrix {
    _Matrix* create(int size) {
        auto matrix = new _Matrix;
        matrix->height = size;
        matrix->weight = size;
        matrix->matrix = (__Matrix) calloc(size * size, sizeof(double));
        return matrix;
    }

    _Matrix* create(int size, int num) {
        auto matrix = new _Matrix;
        matrix->height = size;
        matrix->weight = size;
        matrix->matrix = (__Matrix) calloc(size * size, sizeof(double));

        for (int i = 0; i < size * size; ++i) {
            matrix->matrix[i] = num;
        }
        return matrix;
    }

    _Matrix* create(int height, int weight, int num) {
        auto matrix = new _Matrix;
        matrix->height = height;
        matrix->weight = weight;
        matrix->matrix = (__Matrix) calloc(height * weight, sizeof(double));

        for (int i = 0; i < height * weight; ++i) {
            matrix->matrix[i] = num;
        }
        return matrix;
    }

    void init(_Matrix* matrix) {
        auto size = matrix->weight;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (i == j)
                    matrix->matrix[i * size + j] = 2;
                else
                    matrix->matrix[i * size + j] = 1;
            }
        }
    }

    _Vector* multiply(_Matrix* matrix, _Vector* vector) {
        auto size = matrix->height;
        auto result = Vector::create(size);

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < matrix->weight; ++j) {
                result->vector[i] += matrix->matrix[matrix->weight * i + j] * vector->vector[j];
            }
        }
        return result;
    }

    void print(_Matrix* matrix) {
        auto height = matrix->height;
        auto weight = matrix->weight;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < weight; ++j) {
                std::cout << matrix->matrix[weight * i + j] << " ";
            }
            std::cout << "\n";
        }
    }
}