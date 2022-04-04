//#include "Scenarios.h"
#include "schedule.h"
#include "SquareMatrix.h"
#include <mpich/mpi.h>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*if (rank == 0) {
        Scenarios::givenSolution(2200);
        Scenarios::arbitraryDecision(600);
    }*/
    _Matrix matrix;
    if (rank == 0) {
        matrix = Matrix::create(3, 2);
        //Matrix::print(matrix, 3);
    } else {
        matrix = Matrix::create(3);
    }
    schedule::send_matrix(5, 3, matrix);

    if (rank < size) {
        //cout << endl;
        Vector::print(matrix, 3);
        cout << endl;
    }

    return 0;
}
