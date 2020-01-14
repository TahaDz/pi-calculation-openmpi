	// RAHMANI TAHA ABDELAZIZ

#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    // Calculating the start and the end of each process's interval 
    float start =   world_rank * (1.0/world_size);
    float end = world_rank * (1.0/world_size) + (1.0/world_size);
    // Calculating the integral of each sub-interval
    float pi = 4*(atan(end)-atan(start)); 
    // PI_FINAL the value of pi
    float PI_FINAL = pi;

     // test if its a master or woker
 if (world_rank == 0) {

    double startwtime, endwtime;
    startwtime = MPI_Wtime();
    for(int i=1;i<world_size;i++)
    {
	// receive all parts of pi 
       MPI_Recv(&pi, 1, MPI_FLOAT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
	printf("PI = %f\n",pi);
       PI_FINAL +=pi;
    }
    printf("PI = %f\n",PI_FINAL); 
    endwtime = MPI_Wtime();
    printf ( "Wall clock time = %f \n", endwtime-startwtime );  
} 
else{
    // send the part calculated by the worker process to the master
    MPI_Send(&pi, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD); 
}


    // Finalize the MPI environment.
    MPI_Finalize();
}













