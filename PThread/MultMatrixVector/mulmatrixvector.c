#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Global variable:
accessible to all threads */
int thread_count;
int m;
int n;
int * x;
int ** A;
int * y;

void * threadMatVector(void * rank){
    long my_rank = (long) rank;
    printf("%ld\n", my_rank);
    int i, j;
    int local_m = m/thread_count;
    int myFirstRow = my_rank * local_m;
    int myLastRow = (my_rank + 1) * local_m - 1;
    for(i = myFirstRow; i <= myLastRow; i++){
        y[i] = 0;
        for(j = 0; j < n; j++){
            y[i] += A[i][j] * x[j];
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    long thread; /* Use long in case of a 64 − bit system */
    pthread_t* thread_handles;
    /* Get number of threads from command line */
    thread_count = strtol(argv[1], NULL, 10);
    thread_handles = malloc (thread_count * sizeof(pthread_t));

    m = 12;
    n = 12;
    x = malloc (m * sizeof(int));
    y = malloc (m * sizeof(int));
    A = malloc (n * sizeof(int *));

    for(int i = 0; i < n; i++){
        A[i] = malloc (m * sizeof(int));
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            A[i][j] = i * m + j;
        }
    }
    /*for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }*/
    for(int j = 0; j < m; j++){
        x[j] = j;
    }


    for (thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_handles[thread], NULL, threadMatVector, (void*) thread);
    
    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);


    for(int j = 0; j < m; j++){
        printf("%d ", y[j]);
    }

    free(thread_handles);
    for(int i = 0; i < n; i++){
        free(A[i]);
    }
    free(A);
    free(x);
    printf("\n");
    return 0;
}
/* main */


