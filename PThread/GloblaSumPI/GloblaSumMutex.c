#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int thread_count;
pthread_mutex_t mutex;
double sum = 0;
int n = 1024;

void * threadSum (void * rank){
    long my_rank = (long) rank;
    double factor;
    long long i;
    long long myN = n/thread_count;
    long long myFirstI = myN * my_rank;
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
    pthread_mutex_lock(&mutex);
    sum += mySum;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main (int arc, char* argv[]){
    long thread; /* Use long in case of a 64 − bit system */
    pthread_t* thread_handles;
    /* Get number of threads from command line */
    thread_count = strtol(argv[1], NULL, 10);
    thread_handles = malloc (thread_count * sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);
    for(long i = 0; i < thread_count; i++){
        pthread_create(thread_handles + i, NULL, threadSum, (void*) i);
        //pthread_create(&thread_handles[i], NULL, threadSum, (void*) i);
    }
    for(long i = 0; i < thread_count; i++){
        pthread_join(thread_handles[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("%f\n", 4*sum);
    return 0;
}
