#pragma once

#include <vector>


class Vector {
    friend class SquareMatrix;
private:
    std::vector<double> data;
public:
    explicit Vector(size_t size);
    Vector(size_t size, double num);
    explicit Vector(std::vector<double>& v);

    void initWithSinus(double size);
    Vector operator*(double num);
    Vector operator-(Vector vector);
    double operator[] (int index);
    double measure();
    double max();
    void print();
    explicit operator std::vector<double>&();
};


