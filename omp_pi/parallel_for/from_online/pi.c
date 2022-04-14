#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <omp.h>
#include <math.h>
#include <sys/time.h>

const double PI = 3.1415926535897932;
const long STEP_NUM = 10000000;
const double STEP_LENGTH = 1.0 / 10000000;

int main(int argc, char **argv)
{
    struct timeval startTime;
    gettimeofday(&startTime, NULL);

    double sum = 0.0;
    double pi, x;

    int thread_count = strtol(argv[1], NULL, 10);


    //printf("\nStart calculating...\n");
    // computational steps
#pragma omp parallel for reduction(+:sum) private(x) num_threads(thread_count)
    for(int i = 0;i < STEP_NUM; i++)
    {
        x = (i + 0.5) * STEP_LENGTH;
        sum += 1.0 / (1.0 + x * x);
    }
    pi = STEP_LENGTH * sum * 4;

    struct timeval endTime;
    gettimeofday(&endTime, NULL);
    printf("PI = %.16lf with error %.16lf\nTime elapsed : %lf seconds.\n\n", pi, fabs(pi - PI), (endTime.tv_sec - startTime.tv_sec) + ((double)(endTime.tv_usec - startTime.tv_usec) / 10E6 ));
    assert(fabs(PI - pi) <= 0.001);
    return 0;
}