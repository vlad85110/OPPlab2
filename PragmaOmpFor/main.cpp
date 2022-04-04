#include "Scenarios.h"
#include "reduction.h"

int main() {
    //Scenarios::givenSolution(2200);
    //Scenarios::arbitraryDecision(600);

    std::cout << factorial(4) << std::endl;
    std::cout << sum(1, 1, 5) << std::endl;

    omp_set_num_threads(4);
    int a = 0;
    #pragma omp parallel reduction(+:a)
        {
            a += omp_get_thread_num();
        }
    std::cout << a << std::endl;
    return 0;
}
