//#include "Scenarios.h"
#include "schedule.h"
#include "SquareMatrix.h"
#include "Scenarios.h"
#include <mpich/mpi.h>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {

        //Scenarios::arbitraryDecision(600);
    }
    //Scenarios::givenSolution(2200);


    _Vector* a = Vector::create(2, 1);
    a = schedule::join_vector(a, 6);
    if (rank == 0) {
        Vector::print(a);
    }


    return 0;
}
