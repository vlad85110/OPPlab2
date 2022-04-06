#include "Scenarios.h"
#include <mpi.h>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //if (rank == 0) {

        //Scenarios::arbitraryDecision(600);
    //}
    Scenarios::givenSolution(3);
    return 0;
}
