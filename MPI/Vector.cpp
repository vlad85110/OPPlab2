#include "Vector.h"
#include <iostream>
#include <cmath>
#include <algorithm>

static const double PI = 3.14159265358979323846;
using std::cout;
using std::endl;

namespace Vector {
    _Vector create(size_t size) {
        return (_Vector)calloc(size, sizeof(double));
    }

    _Vector create(size_t size, double num) {
        auto _new = new double [size];
        for (int i = 0; i < size; ++i) {
            _new[i] = num;
        }
        return _new;
    }

    _Vector multiply(_Vector vector, double num, int size) {
        auto _new = create(size);
        for (int i = 0; i < size; ++i) {
            _new[i] = vector[i] * num;
        }
        return _new;
    }

    double measure(_Vector vector, int size) {
        double mes = 0, s = 0;

        for (auto i = 0; i < size; ++i) {
            s += vector[i] * vector[i];
        }
        //MPI_Reduce(&s, &mes, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        return sqrt(s);
    }

    _Vector minus(_Vector vector1, _Vector vector2, int size) {
        _Vector res = create(size);

        for (auto i = 0; i < size; ++i) {
            res[i] = vector1[i] - vector2[i];
        }

        return res;
    }

    void initWithSinus(_Vector vector, double size) {
        for (auto i = 0; i < size; ++i) {
            vector[i] = sin(2 * PI * i / size);
        }
    }

    double max_el(_Vector vector, int size) {
        return *std::max_element(vector, vector + size);
    }

    void print(_Vector vector, int size) {
        for (int i = 0; i < size; ++i) {
            std::cout << vector[i] << std::endl;
        }
    }
}