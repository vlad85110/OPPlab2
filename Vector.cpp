#include "Vector.h"
#include <iostream>
#include <cmath>


static const double PI = 3.14159265358979323846;

Vector::Vector(size_t size, double num) : data(size, num) {}

Vector::Vector(size_t size) : data(size, 0) {}

Vector::Vector(std::vector<double>& v) : data(v){}

void Vector::print() {
    for (auto it : data) {
        std::cout << std::fixed << it << std::endl;
    }
}

Vector Vector::operator*(double num) {
    auto size = this->data.size();
    Vector result(size);
    for (auto i = 0; i < size; ++i) {
        result.data[i] = (*this)[i] * num;
    }
    return result;
}

double Vector::measure() {
    double mes = 0;
    for (auto & it: data)
        mes += it * it;
    return sqrt(mes);
}

Vector::operator std::vector<double>&() {
    return data;
}

double Vector::operator[](int index) {
    return data[index];
}

Vector Vector::operator-(Vector vector) {
    auto size = this->data.size();
    Vector result(this->data.size());
    for (auto i = 0; i < size; ++i) {
        result.data[i] = this->data[i] - vector[i];
    }
    return result;
}

void Vector::initWithSinus(double size) {
    for (auto i = 0; i < data.size(); ++i) {
        data[i] = sin(2 * PI * i / size);
    }
}

double Vector::max() {
    return *std::max_element(data.begin(), data.end());
}


