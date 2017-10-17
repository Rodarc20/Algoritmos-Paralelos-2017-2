#include<mpi.h>
#include<stdio.h>
#include<string.h>

int main(void){

    //voy a sumar los ranks, para saber que este correcto
    int comm_sz, my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int sum_recive = 0;
    int local_sum = my_rank;
    int prod = 1;
    int div = my_rank;
    int source = (div + 1) * prod;
    while(!(div & 1) && div >= 0 && source < comm_sz){//>>
        MPI_Recv(&sum_recive, 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        local_sum += sum_recive;
        div >>= 1;
        prod <<= 1;
        source = (div + 1) * prod;
    }
    //printf("id: %d sum recive: %d\n", my_rank, local_sum);
    prod = 1;
    div = my_rank;
    while(!(div & 1) && div > 0){
        div >>= 1;
        prod <<= 1;
    }
    if(div & 1){
        int target = my_rank - prod;
        MPI_Send(&local_sum, 1, MPI_INT, target, 0, MPI_COMM_WORLD);
    }
    else{//supuestamente my_rank == 0
        printf("Suma total: %d\n", local_sum);
    }

    if(my_rank == 0){
    }
    MPI_Finalize();

    
    return 0;
}
