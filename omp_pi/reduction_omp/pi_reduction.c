//
// Created by MD. Zahed on 13/04/2022.
//


//
// Created by MD. Zahed on 13/04/2022.
//
#include <omp.h>
#include <stdio.h>
#include <time.h>

#define PI25DT 3.141592653589793238462643


#define INTERVALS 10000000
//#define INTERVALS 10

double run_loop(int start, int stop, int rank);

int main(int argc, char **argv)
{

    double time2, pi;
    time_t time1 = clock();
    long int intervals = INTERVALS;
    // printf("Number of intervals: %ld\n", intervals);

    int thread_count = strtol(argv[1], NULL, 10);

    int per_thread = intervals / thread_count;
    int left_out = intervals - (thread_count * per_thread);

    double arr[thread_count];


#pragma omp parallel reduction(+: pi) num_threads(thread_count)
    {
        int rank = omp_get_thread_num();

        int start, stop;


        if (rank == thread_count-1) {
            start = intervals;

            if(left_out != 0) {
                stop = intervals - (per_thread + left_out);
            } else {
                stop = intervals - per_thread;
            }

        } else {
            start = ((rank+1) * per_thread);
            stop = (rank * per_thread);
        }


        pi += run_loop(start, stop, rank);
        //arr[rank] = run_loop(start, stop, rank);
    }

/*    int i;
    for (i = 0; i < thread_count; i++) {
        pi = pi + arr[i];
    }*/

    time2 = (clock() - time1) / (double) CLOCKS_PER_SEC;

    printf("Computed PI %.24f\n", pi);
    printf("The true PI %.24f\n", PI25DT);
    printf("Error       %.24f\n", PI25DT-pi);
    printf("Elapsed time (s) = %f\n", time2);
    printf("Threads: %d\n", thread_count);

    return 0;
}


double run_loop(int start, int stop, int rank) {
    long int i, intervals = INTERVALS;
    double x, dx, f, sum;


    sum = 0.0;
    dx = 1.0 / (double) intervals;

    for (i = start ; i > stop; i--) {
        //printf("rank: %d, i: %ld\n", rank, i);
        x = dx * ((double) (i - 0.5));
        f = 4.0 / (1.0 + x*x);
        sum = sum + f;
    }

    //printf("Rank: %d, pi: %f, start: %d, stop: %d\n", rank, dx*sum, start, stop);

    return dx*sum;
}
