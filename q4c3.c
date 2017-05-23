/* File:     mpi_output.c
 *
 * Purpose:  A program in which multiple MPI processes try to print 
 *           a message.
 *
 * Compile:  mpicc -g -Wall -o mpi_output mpi_output.c
 * Usage:    mpiexec -n<number of processes> ./mpi_output
 *
 * Input:    None
 * Output:   A message from each process
 *
 * IPP:      Section 3.3.1  (pp. 97 and ff.)
 */
#include <stdio.h>
#include <mpi.h> 

int main(void) {
   int my_rank, comm_sz, flag=0;

   MPI_Init(NULL, NULL); 
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   if(my_rank==0){
	printf("Proc %d of %d > Does anyone have a toothpick?\n", my_rank, comm_sz);
	MPI_Send(&flag, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
   }
   else{
	MPI_Recv(&flag, 1, MPI_INT, my_rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	printf("Proc %d of %d > Does anyone have a toothpick?\n", my_rank, comm_sz);
	if(my_rank < comm_sz - 1)
		MPI_Send(&flag, 1, MPI_INT, my_rank+1, 0, MPI_COMM_WORLD);
   }

   MPI_Finalize();
   return 0;
}  /* main */
