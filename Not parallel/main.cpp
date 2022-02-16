#include "Scenarios.h"
#include <omp.h>
#include <fstream>


int main() {
    for (int i = 1; i <= 12; ++i) {
    omp_set_num_threads(i);
    Scenarios::givenSolution(2200);
    Scenarios::arbitraryDecision(600);
    }

    return 0;
}
