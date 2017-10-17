#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

double f(double x){
    return x*x;
}

void threadSum (double a, double b, int n, double * global_result_p){
    double h, x, my_result;
    double locala, localb;
    int localn;
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    h = (b-a)/n;
    localn = n/thread_count;
    locala = a + my_rank*localn*h;
    localb = locala + localn*h;
    my_result = (f(locala) + f(localb))/2.0;
    for(int i = 1; i <= localn-1; i++){
        x = locala + i*h;
        my_result += f(x);
    }
    my_result *= h;
    #pragma omp critical
    *global_result_p += my_result;

}

int main (int arc, char* argv[]){
    double global_result = 0.0;
    double a, b;
    int n;
    int thread_count;
    /* Get number of threads from command line */
    thread_count = strtol(argv[1], NULL, 10);
    printf("Enter a, b, and n\n");
    scanf("%lf %lf %d", &a, &b, &n);
    #pragma omp parallel num_threads(thread_count)
    threadSum(a,b,n, &global_result);
    printf("%.14e\n", global_result);
    return 0;
}


