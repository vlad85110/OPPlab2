#pragma once

#include "Matrix.h"
#include <vector>

class SquareMatrix : public Matrix{
private:
    std::vector<double> data;
    size_t size;
public:
    explicit SquareMatrix(size_t size);
    void init() override;
    std::shared_ptr<Matrix> operator*(std::shared_ptr<Matrix>) override;
    double operator[] (int index) override;
    void operator*(double num) override;
    double measure() override;
    void print() override;
    ~SquareMatrix() override;
};


