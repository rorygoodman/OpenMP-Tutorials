#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 4
static long num_steps =100000;
double step;
int main(){
	int i,nthreads;
	double pi, sum;
    sum=0.0;
    step = 1.0/(double) num_steps;
    
    omp_set_num_threads(NUM_THREADS);
    int n_threads;
#pragma omp parallel
    {	
    	int id,i,nthrds;
    	double x;
    	id = omp_get_thread_num();
    	nthrds=omp_get_num_threads();
    	if(id==0) nthreads=nthrds;
	    for (i=id;i<num_steps;i+=nthrds) {
	        x = (i+0.5)*step;
        #pragma omp critical
        {
	        sum += 4.0/(1.0+x*x);
        }
    }
    }

    	pi=sum*step;
    printf("pi=%f\n",pi);
    return 0;
}