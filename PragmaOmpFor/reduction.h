#pragma once
#include <omp.h>

long long factorial(int num) {
    omp_set_num_threads(num);
    long long res = 1;
    #pragma omp parallel reduction(*:res)
    {
        res += omp_get_thread_num();
    }
    return res;
}

long long sum(int a1, int d, int num) {
    omp_set_num_threads(num - 1);
    long long res = 0;
    #pragma omp parallel reduction(+:res)
    {
        res += (omp_get_thread_num() + 2) * d;
    }
    return res + a1;
}