#pragma once

#include <vector>
// 184 50
#define CHUNK_SIZE 50


class Vector {
    friend class SquareMatrix;
private:
    std::vector<double> data;
public:
    explicit Vector(size_t size);
    Vector(size_t size, double num);
    [[maybe_unused]] explicit Vector(std::vector<double>& v);

    void initWithSinus(double size);
    Vector operator*(double num) const;
    Vector operator-(const Vector &vector) const;
    double operator[] (int index) const;
    std::vector<double>& getVector ();
    Vector& operator=(const Vector &vector);
    [[nodiscard]] double measure() const;
    [[nodiscard]] double max() const;
    void print() const;
    explicit operator std::vector<double>&();
};


