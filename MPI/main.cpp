#include "Scenarios.h"
#include <mpi.h>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    Scenarios::arbitraryDecision(600);

    Scenarios::givenSolution(2200);

    MPI_Finalize();
    return 0;
}
