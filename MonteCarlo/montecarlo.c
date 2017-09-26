#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <time.h>
#include <stdlib.h>


int main(void) {
    int comm_sz;
    int my_rank;

    long long int local_number_in_circle, number_in_circle;
    long int number_tosses = 1000000;
    //int source;
    srand(time(NULL));   // should only be called once
    //int r = rand(); 
     
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    local_number_in_circle = 0;
    number_in_circle = 0;

    for(long int toss = 0; toss < number_tosses; toss++){
        double x = ((double)(rand()%10000))/10000 * ((rand()&1) *-1);
        double y = ((double)(rand()%10000))/10000 * ((rand()&1) *-1);
        //printf("%f, %f\n", x, y);
        double distance =  x*x + y*y;
        if(distance <= 1)
            local_number_in_circle++;
    }

    MPI_Reduce(&local_number_in_circle, &number_in_circle, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);


    if(my_rank == 0){
        double pi = 4*number_in_circle/((double) number_tosses);
        printf("pi = %f\n", pi);
    }
    MPI_Finalize();
    return 0;
}
