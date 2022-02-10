#pragma once

#include "Matrix.h"
#include "SquareMatrix.h"
#include <vector>


class Vector : public Matrix{
    friend class SquareMatrix;
private:
    std::vector<double> data;
public:
    explicit Vector(size_t size);
    Vector(size_t size, double num);
    explicit Vector(std::vector<double>& v);
    void init() override;
    std::shared_ptr<Matrix> operator*(std::shared_ptr<Matrix>) override;
    void operator*(double num) override;
    double operator[] (int index) override;
    double measure() override;
    void print() override;
    explicit operator std::vector<double>&();
    ~Vector() override;
};


