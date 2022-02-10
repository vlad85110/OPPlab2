#include "Vector.h"
#include <iostream>
#include <cmath>


Vector::Vector(size_t size, double num) : data(size, num) {}

Vector::Vector(size_t size) : data(size, 0) {}

Vector::Vector(std::vector<double>& v) : data(v){}

void Vector::init() {
    throw std::runtime_error("Vector is already inited");
}

std::shared_ptr<Matrix> Vector::operator*(std::shared_ptr<Matrix>) {
    throw std::runtime_error("It's not a matrix");
}

void Vector::print() {
    for (auto it : data) {
        std::cout << it << std::endl;
    }
}

void Vector::operator*(double num) {
    for (double & it : data) {
        it *= num;
    }
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

Vector::~Vector() = default;


