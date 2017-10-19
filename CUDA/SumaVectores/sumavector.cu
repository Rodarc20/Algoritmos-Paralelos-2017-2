#include<stdio.h>
#include<string>

__global__
void vecAddKernel(float * a, float * b, float * c, int n){//funcion ejecutada en la gpu, osea la funcion device
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i < n)
        *(c+i) = *(a+i) + *(b+i);//c[i] = a[i] + b[i]
}

void vecAdd(float * a, float * b, float * c, int n){
    int size = n * sizeof(float);//calcular el tamaño de memoria de los vectores
    float * d_a, * d_b, * d_c;
    cudaMalloc((void **) & d_a, size);//creacion de los vectores en la memoria del gpu. //es necesario el void **?
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);//destino, origen, tamaño, 
    cudaMalloc((void **) & d_b, size);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
    cudaMalloc((void **) & d_c, size);

    //llamada al la funcon kernel con ciertos parametros
    //<<<numero de bloques, tamaño de los bloques>>>, el numero de bloques es el techo de (tamaño de elementos / tamaño del bloque), el tamaño del bloque es el numero de threads del bloque
    //el numero recibido por la funcion ceil (techo) debe ser un flotante, por eso el .0
    vecAddKernel<<<ceil(n/256.0), 256>>> (d_a, d_b, d_c, n);

    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
    
    //liberando memoria del device
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
}

int main(){
    int n = 1 << 20;//probar con 20
    float * a, * b, * c;
    a = (float *)malloc(n*sizeof(float));//los malloc fevuelven un tipo void * ahy que convertirlo a lfoat *
    b = (float *)malloc(n*sizeof(float));
    c = (float *)malloc(n*sizeof(float));

    for(int i = 0; i < n; i++){
        *(a+i) = i;
        *(b+i) = i;
    }
    vecAdd(a, b, c, n);
    /*for(int i = 0; i < n; i++){
        printf("%f ", *(c+i));
    }*/
    printf("Finalizado\n");
    return 0;
}
