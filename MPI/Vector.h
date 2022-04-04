#pragma once

#include <vector>
#include <mpi.h>

using _Vector = double*;

namespace Vector {
    _Vector create(size_t size);
    _Vector create(size_t size, double num);

    void initWithSinus(_Vector vector, double size);
    _Vector multiply(_Vector vector, double num, int size);
    _Vector minus(_Vector vector1, _Vector vector2, int size);
    double measure(_Vector vector, int size);
    double max_el(_Vector vector, int size);
    void print(_Vector vector, int size);
}

