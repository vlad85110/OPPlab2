#include "Vector.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <omp.h>


const int threads = omp_get_num_threads();
static const double PI = 3.14159265358979323846;

Vector::Vector(size_t size, double num) : data(size, num) {}

Vector::Vector(size_t size) : data(size, 0) {}

[[maybe_unused]] Vector::Vector(std::vector<double>& v) : data(v){}

void Vector::print() const {
    for (auto it : data) {
        std::cout << std::fixed << it << std::endl;
    }
}

Vector Vector::operator*(double num) const {
    auto size = this->data.size();
    Vector result(size);

    #pragma omp parallel for schedule (static, CHUNK_SIZE)
    for (auto i = 0; i < size; ++i) {
        result.data[i] = (*this)[i] * num;
    }
    return result;
}

double Vector::measure() const {
    auto size = this->data.size();
    double mes = 0;
    #pragma omp parallel reduction (+:mes)
    {
    #pragma omp for schedule (static, CHUNK_SIZE)
    for (auto i = 0; i < size; ++i)
        mes += data[i] * data[i];
    }
    return sqrt(mes);
}

Vector::operator std::vector<double>&() {
    return data;
}

double Vector::operator[](int index) const {
    return data[index];
}

Vector Vector::operator-(const Vector &vector) const {
    auto size = this->data.size();
    Vector result(this->data.size());

    #pragma omp parallel for schedule (static, CHUNK_SIZE)
    for (auto i = 0; i < size; ++i) {
        result.data[i] = this->data[i] - vector[i];
    }
    return result;
}

void Vector::initWithSinus(double size) {
    #pragma omp parallel for schedule (static, CHUNK_SIZE)
    for (auto i = 0; i < data.size(); ++i) {
        data[i] = sin(2 * PI * i / size);
    }
}

double Vector::max() const {
    return *std::max_element(data.begin(), data.end());

}

std::vector<double>& Vector::getVector() {
    return data;
}

Vector& Vector::operator=(const Vector& v) = default;



