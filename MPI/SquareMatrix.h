#pragma once

#include "Vector.h"

using __Matrix = double*;
using _Matrix = struct matrix;

struct matrix {
    __Matrix matrix;
    int height;
    int weight;
};

namespace Matrix {
    _Matrix *create(int size);

    _Matrix *create(int size, int num);

    _Matrix *create(int height, int weight, int num);

    void init(_Matrix *matrix);

    _Vector* multiply(_Matrix *matrix, _Vector* vector);

    [[maybe_unused]] void print(_Matrix* matrix);
}