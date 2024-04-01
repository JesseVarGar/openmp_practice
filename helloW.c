#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

/*
    gcc -fopenmp fileName.c
    Use the command above to compile all openMP code
*/

int main() 
{
    #pragma omp parallel
    {
        int id = omp_get_thread_num(); 
        printf("Hello(%d)", id);
        printf(" World(%d)\n", id);
    }
}