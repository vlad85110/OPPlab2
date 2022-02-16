#pragma once

#include <vector>
#include "Vector.h"


class SquareMatrix {
private:
    std::vector<double> data;
    size_t size;
public:
    explicit SquareMatrix(size_t size);
    void init();

    Vector operator*(Vector &vector) const;
    double operator[] (int index) const;
    [[maybe_unused]] void print() const;
};