#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int thread_count;
double sum = 0;
int n = 1024;

void threadSum (int rank){
    double factor;
    long long i;
    long long myN = n/thread_count;
    long long myFirstI = myN * rank;
    long long myLastI = myFirstI + myN;
    double mySum = 0;
    //este if no es necesario, solo bataria verificar si es impar o no dentro del la operacion bueno djarlo asi
    if(myFirstI & 1){//si es impar
        factor = -1;
    }
    else{
        factor = 1;
    }

    for(i = myFirstI; i < myLastI; i++, factor = -factor){
        mySum += factor/(2*i + 1);
    }
    sum += mySum;
}

int main (int arc, char* argv[]){
    long thread; /* Use long in case of a 64 − bit system */
    pthread_t* thread_handles;
    /* Get number of threads from command line */
    thread_count = strtol(argv[1], NULL, 10);
    //double sum = 0;
    double factor;
    #pragma omp parallel for num_threads(thread_count) reduction (+:sum) private (factor)
    for(long i = 0; i < n; i++){
        if(i&1){
            factor = -1;
        }
        else{
            factor = 1;
        }
        sum+=factor/(2*i+1);
    }
    printf("%f\n", 4*sum);
    return 0;
}

