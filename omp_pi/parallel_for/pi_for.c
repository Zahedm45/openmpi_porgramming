//
// Created by MD. Zahed on 13/04/2022.
//
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#define PI25DT 3.141592653589793238462643
//#define INTERVALS 10000000
#define INTERVALS 10000000


int main(int argc, char **argv)
{

    double pi;
    double start_time, end_time, exec_time;
    start_time = omp_get_wtime();

    long int intervals = INTERVALS;
    int thread_count = strtol(argv[1], NULL, 10);



    double x, sum = 0.0;
    double dx = 1.0 / (double) intervals;

    //long int i;
#pragma omp parallel for reduction(+:sum) private(x) num_threads(thread_count)
        for (long int i = intervals ; i > 0; i--) {
            x = dx * ((double) (i - 0.5));
            sum += 4.0 / (1.0 + x*x);
        }



    pi += dx*sum;

    end_time = omp_get_wtime();
    exec_time = end_time - start_time;

    printf("Computed PI %.24f\n", pi);
    printf("The true PI %.24f\n", PI25DT);
    printf("Error       %.24f\n", PI25DT-pi);
    printf("Elapsed time (s) = %f\n",exec_time);

    printf("Threads: %d\n", thread_count);

    return 0;
}

