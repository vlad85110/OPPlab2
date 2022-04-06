#include "Vector.h"

#include <iostream>
#include <cmath>

#include <algorithm>

static const double PI = 3.14159265358979323846;
using std::cout;
using std::endl;

namespace Vector {
    _Vector* create(size_t size) {
        auto vector = new _Vector;
        vector->size = size;
        vector->vector = (__Vector) calloc(size, sizeof(double));
        return vector;
    }

    _Vector* create(size_t size, double num) {
        auto vector = new _Vector;
        vector->size = size;
        vector->vector = (__Vector) calloc(size, sizeof(double));

        for (int i = 0; i < size; ++i) {
            vector->vector[i] = num;
        }
        return vector;
    }

    _Vector* multiply(_Vector* vector, double num) {
        auto _new = create(vector->size);
        for (int i = 0; i < vector->size; ++i) {
            _new->vector[i] = vector->vector[i] * num;
        }
        return _new;
    }

    double measure(_Vector* vector, int chunk) {
        int rank, size;

        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        double mes = 0, s = 0;

        for (int i = 0; i < vector->size; ++i) {
            s += vector->vector[i] * vector->vector[i];
        }

        MPI_Reduce(&s, &mes, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        return sqrt(mes);
    }

    _Vector* minus(_Vector* vector1, _Vector* vector2) {
        auto res = create(vector1->size);

        for (auto i = 0; i < vector1->size; ++i) {
            res->vector[i] = vector1->vector[i] - vector2->vector[i];
        }

        return res;
    }

    void initWithSinus(_Vector* vector) {
        double size = vector->size;
        for (auto i = 0; i < vector->size; ++i) {
            vector->vector[i] = sin(2 * PI * i / size);
        }
    }

    double max_el(_Vector* vector) {
        return *std::max_element(vector->vector, vector->vector + vector->size);
    }

    void print(_Vector* vector) {
        for (int i = 0; i < vector->size; ++i) {
            std::cout << vector->vector[i] << std::endl;
        }
    }

    void free (_Vector* vector) {
        ::free(vector->vector);
        ::free(vector);
    }
}