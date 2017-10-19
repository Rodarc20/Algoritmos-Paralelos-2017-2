#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

void OddEvenSort1(int * a, int n){
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

void OddEvenSort2(int * a, int n){
    int phase, i, temp;
    #pragma omp parallel num_threads(thread_count) default(none) shared(a, n) private(i, tmp, phase)
    for(phase = 0; phase < n; phase++){
        if(phase & 1){//impar
            #pragma omp for
            for(i = 1; i < n; i += 2){
                if(a[i-1] > a[i]){
                    tmp = a[i-1];
                    a[i-1] = a[i];
                    a[i] = tmp;
                }
            }
        }
        else{
            #pragma omp for
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
    /* Get number of threads from command line */
    thread_count = strtol(argv[1], NULL, 10);
    int n = 1000;
    int * a = in 
    return 0;
}

