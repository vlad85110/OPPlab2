#pragma once
#include <mpi.h>

namespace schedule {
    int round_up(int x, int y) {
        return x / y + ((x % y != 0) ? 1 : 0);
    }

    int get_chunk(int array_size, int mpi_size) {
        return round_up(array_size, mpi_size);
    }

    void send_matrix(int num_p, int size, double *matrix) {
        int rank, mpi_size;

        MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        int chunk = get_chunk(size, mpi_size);

        for (int i = 1; i < chunk * size; ++i) {
            if (rank == 0) {
                MPI_Send(matrix, size * chunk, MPI_DOUBLE, i, 123, MPI_COMM_WORLD);
            }
            if (rank == i) {
                MPI_Recv(matrix, size * chunk, MPI_DOUBLE, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            //MPI_Barrier(MPI_COMM_WORLD);//TODO
        }
    }

}

