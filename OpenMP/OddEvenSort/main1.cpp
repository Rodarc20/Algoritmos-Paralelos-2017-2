#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

void OddEvenSort(int * a, int n){
    int phase, i, temp;
    for(phase = 0; phase < n; phase++){
        if(phase & 1){//impar
            #pragma omp parallel for num_threads(thread_count) default(none) shared(a, n) private(i, tmp)
            for(i = 1; i < n; i += 2){
                if(a[i-1] > a[i]){
                    tmp = a[i-1];
                    a[i-1] = a[i];
                    a[i] = tmp;
                }
            }
        }
        else{
            #pragma omp parallel for num_threads(thread_count) default(none) shared(a, n) private(i, tmp)
            for(i = 1; i < n-1; i += 2){
                if(a[i] > a[i+1]){
                    tmp = a[i+1];
                    a[i+1] = a[i];
                    a[i] = tmp;
                }
            }
        }
    }
}

int main (int arc, char* argv[]){
    long thread; /* Use long in case of a 64 − bit system */
    pthread_t* thread_handles;
    /* Get number of threads from command line */
    thread_count = strtol(argv[1], NULL, 10);
    //double sum = 0;
    double factor;
    for(phase = 0
    return 0;
}


