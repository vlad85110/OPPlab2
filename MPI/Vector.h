#pragma once

#include <vector>
#include <mpi.h>

using __Vector = double*;
using _Vector = struct vector;

struct vector {
    __Vector vector;
    int size;
};


namespace Vector {
    _Vector* create(size_t size);
    _Vector* create(size_t size, double num);

    void initWithSinus(_Vector* vector);
    _Vector* multiply(_Vector* vector, double num);
    _Vector* minus(_Vector* vector1, _Vector* vector2);
    double measure(_Vector* vector);
    double max_el(_Vector* vector);
    void print(_Vector* vector);
}

