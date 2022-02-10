#pragma once

#include <vector>
#include <memory>


class Matrix {
public:
    virtual void init() = 0;
    virtual std::shared_ptr<Matrix> operator*(std::shared_ptr<Matrix>) = 0;
    virtual void operator*(double num) = 0;
    virtual double operator[] (int index) = 0;
    virtual std::shared_ptr<Matrix> operator-(std::shared_ptr<Matrix>) = 0;
    virtual double measure() = 0;
    virtual void print() = 0;
    virtual ~Matrix() = default;
};

