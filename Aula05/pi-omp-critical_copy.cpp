#include <stdio.h>
#include <omp.h>
 
double pi_omp_critical(long num_steps) {
    double step = 1.0/(double) num_steps;
    double sum = 0;

    #pragma omp parallel for reduction (+:sum)
    for (long i = 0; i < num_steps; i++) {
        double x = (i-0.5)*step;
        #pragma omp critical
        sum += 4.0/(1.0+x*x);
    }


    return sum * step;
}

int main () {
    long num_steps = 1000000000;
    double pi;
    double start_time, run_time;

    start_time = omp_get_wtime();
    pi = pi_omp_critical(num_steps);
    run_time = omp_get_wtime() - start_time;
    printf("\n pi with %ld steps is %.12lf in %lf seconds\n ",num_steps,pi,run_time);
    return 0;
}

