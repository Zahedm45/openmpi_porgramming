//
// Created by MD. Zahed on 13/04/2022.
//
#include <omp.h>
#include <stdio.h>
#include <time.h>

#define PI25DT 3.141592653589793238462643

#define INTERVALS 10000000

double run_loop();

int main(int argc, char **argv)
{

    double time2, pi;
    time_t time1 = clock();

   // printf("Number of intervals: %ld\n", intervals);


    int thread_count = strtol(argv[1], NULL, 10);
    #pragma omp parallel num_threads(thread_count)
    {
        pi = run_loop();
    }


    time2 = (clock() - time1) / (double) CLOCKS_PER_SEC;

    printf("Computed PI %.24f\n", pi);
    printf("The true PI %.24f\n", PI25DT);
    printf("Error       %.24f\n", PI25DT-pi);
    printf("Elapsed time (s) = %f\n", time2);
    printf("Threads: %d\n", thread_count);

    return 0;
}


double run_loop() {
    long int i, intervals = INTERVALS;
    double x, dx, f, sum, pi;

    int my_rank = omp_get_thread_num();

    printf("Rank: %d\n", my_rank);


    sum = 0.0;
    dx = 1.0 / (double) intervals;
    for (i = intervals; i >= 1; i--) {
        x = dx * ((double) (i - 0.5));
        f = 4.0 / (1.0 + x*x);
        sum = sum + f;
    }

    return pi = dx*sum;
}