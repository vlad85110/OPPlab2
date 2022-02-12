#include "Scenarios.h"
#include <iostream>
#include <omp.h>


int main() {
    omp_set_num_threads(2);

    Scenarios::givenSolution(2200);
    Scenarios::arbitraryDecision(600);

    return 0;
}
