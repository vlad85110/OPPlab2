#pragma once
#include "SquareMatrix.h"
#include <iostream>
#include <mpi.h>

namespace schedule {
    int round_up(int x, int y) {
        return x / y + ((x % y != 0) ? 1 : 0);
    }

    int get_chunk(int array_size, int mpi_size) {
        return round_up(array_size, mpi_size);
    }

    _Matrix* send_matrix(_Matrix* matrix) {
        int rank, mpi_size;
        MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        int size;
        if (rank == 0) {
            size = matrix->height;
        }
        MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);

        int chunk = get_chunk(size, mpi_size);
        double* data;
        if (rank == 0) {
            data = matrix->matrix;
        }

        int len = size * chunk;
        int height, weight;

        for (int i = 1; i < mpi_size; ++i) {
            data += size * chunk;
            height = chunk;
            weight = size;

            if (rank == 0) {
                if (data + len > (matrix->matrix + matrix->height * matrix-> weight)) {
                    len = (matrix->matrix + matrix->height * matrix->weight) - data;
                    height = len / weight;
                }

                MPI_Send(&height, 1, MPI_INT, i,125, MPI_COMM_WORLD);
                MPI_Send(&len, 1, MPI_INT, i,124, MPI_COMM_WORLD);
                MPI_Send(data, len, MPI_DOUBLE, i, 123, MPI_COMM_WORLD);
            }

            if (rank == i) {
                MPI_Recv(&height, 1, MPI_INT, 0, 125, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&len, 1, MPI_INT, 0, 124, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                matrix = Matrix::create(height, weight, 0);
                MPI_Recv(matrix->matrix, len, MPI_DOUBLE, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }

        if (rank == 0) {
            matrix->height = size * chunk / weight;
        }

        return matrix;
    }

    _Vector* join_vector(_Vector* vector, int size) {
        int rank, mpi_size, len;
        auto res = Vector::create(size);
        double* data = res->vector;

        MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

       //todo self send

        for (int i = 1; i < mpi_size; ++i) {
            if (rank == 0) {
                MPI_Recv(&len, 1, MPI_INT, i, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(data, len, MPI_DOUBLE, i, 124, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                data += len;
            }

            if (rank == i) {
                len = vector->size;
                MPI_Send(&len, 1, MPI_INT, 0, 123, MPI_COMM_WORLD);
                MPI_Send(vector->vector, len, MPI_DOUBLE, 0, 124, MPI_COMM_WORLD);
            }
        }
        MPI_Bcast(res->vector, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        return res;
    }
}

