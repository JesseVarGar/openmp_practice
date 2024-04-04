/*
    gcc -fopenmp fileName.c
    Use the command above to compile all openMP code

	omp_init_lock()
	omp_set_lock()
	omp_unset_lock()
	omp_test_lock()
	omp_destroy_lock()
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define numInts 100000
#define bins 10

void main()
{
	time_t t;
	double start_time, run_time;
	srand((unsigned) time(&t));
	int myInts[100000];
	int histogram[bins];
	omp_set_dynamic(0);
	omp_set_num_threads(omp_get_max_threads());
	omp_lock_t locks[bins];
	
	for(int i = 0; i < numInts; i++){
		myInts[i] = rand()%10;
		if(i < bins){
			histogram[i] = 0;
			omp_init_lock(&locks[i]);
		}
	}

	////////////////////////////////////	
	start_time = omp_get_wtime();

	#pragma omp parallel for shared(locks)
	for(int i = 0; i < numInts; i++){
		int val = myInts[i];
		if(omp_test_lock(&locks[val])){
			histogram[val] += 1;
			omp_unset_lock(&locks[val]);
		}
	}
	printf("parallel\n");

	// for(int i = 0; i < numInts; i++){
	// 	int val = myInts[i];
	// 	histogram[val] += 1;
	// }
	// printf("serial\n");

	run_time = omp_get_wtime() - start_time;
	////////////////////////////////////

	for(int i = 0; i < bins; i++){
		omp_destroy_lock(&locks[i]);
	}

	printf("Time: %f\n", run_time);
}
