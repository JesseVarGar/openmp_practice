/*
    gcc -fopenmp fileName.c -o filename
    Use the command above to compile all openMP code
*/

// int omp_get_num_treads()
// int omp_get_thread_num()
// double omp_get_wtime()

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
static long num_steps = 1000000;
#define NUM_THREADS 2
double step;

// static long num_steps = 100000;
// double step;
// int main()
// {
// 	int i;
// 	double x, pi, sum = 0.0;
	
// 	for (i = 0; i < num_steps; i++){
// 		x = (i+0.5)*step;
// 		sum = sum + 4.0/(1.0+x*x);
// 	}
// 	pi = step * sum;
// 	printf("pi = %d\n", pi);
// }


void main()
{
	int i, nthreads;
	double start_time, run_time, pi, sum[NUM_THREADS];
	step = 1.0/(double)num_steps;
	omp_set_num_threads(NUM_THREADS);

    start_time = omp_get_wtime();

	#pragma omp parallel
	{
		int i, id, nthrds;
		double x;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		if (id==0) nthreads = nthrds;
		for (i = id, sum[id]=0.0; i < num_steps; i+=nthrds){
			x = (i+0.5)*step;
			sum[id] += 4.0/(1.0+x*x);
		}
	}

    run_time = omp_get_wtime() - start_time;

	for(i=0, pi=0.0; i<nthreads; i++) pi+= sum[i] * step;
	printf("pi = %f\n", pi);
}