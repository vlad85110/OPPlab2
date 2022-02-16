#include "Scenarios.h"
#include <omp.h>


int main() {

    omp_set_num_threads(12);
    Scenarios::givenSolution(2200);
    Scenarios::arbitraryDecision(600);


    return 0;
}
