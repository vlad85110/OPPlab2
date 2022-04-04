#pragma once

#include <vector>
#include "Vector.h"

using _Matrix = double*;

namespace Matrix {
    _Matrix create(int size);
    _Matrix create(int size, int num);
    void init(_Matrix matrix, int size);

    _Vector multiply(_Matrix matrix, _Vector vector, int size);
    [[maybe_unused]] void print(_Matrix matrix, int size);
}