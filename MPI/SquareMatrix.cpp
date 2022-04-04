#include "SquareMatrix.h"
#include <iostream>

namespace Matrix {
    _Matrix create(int size) {
        return (_Matrix) calloc(size * size, sizeof(double));
    }

    _Matrix create(int size, int num) {
        auto _new = new double [size];
        for (int i = 0; i < size * size; ++i) {
            _new[i] = num;
        }
        return _new;
    }

    void init(_Matrix matrix, int size) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (i == j)
                    matrix[i * size + j] = 2;
                else
                    matrix[i * size + j] = 1;
            }
        }
    }

    _Vector multiply(_Matrix matrix, _Vector vector, int size) {
        _Vector result = Vector::create(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result[i] += matrix[size * i + j] * vector[j];
            }
        }
        return result;
    }

    void print(_Matrix matrix, int size) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << matrix[size * i + j] << " ";
            }
            std::cout << "\n";
        }
    }
}