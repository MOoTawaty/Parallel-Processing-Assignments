#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int p, rank;
    int x, y;
    MPI_Status status;
    /// initializes the MPI environment
    MPI_Init(&argc, &argv);
    ///find the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    ///find the process id
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    ///Master Process
    if(rank == 0)
    {
          printf("Hello Master!\n");
          ///set of numbers between 2 ranges
          printf("Enter UR Range X & Y: \n");
          //x = 1;
          //y = 100;
          scanf("%d", &x);
          scanf("%d", &y);
          if(x == 1)
            x = x+1;
          int r = (y-x)/(p-1);
          int i = 0;
          //int suby, subx;
          for(i=1; i<p ; i++){
                  int suby, subx;
            suby =  x + ((i)* r);
            subx = x + ((i-1)* r);
            MPI_Send(&subx, 1, MPI_INT, i , 0, MPI_COMM_WORLD);
            MPI_Send(&suby , 1, MPI_INT, i , 0, MPI_COMM_WORLD);
          }

          int j=0;
          for(j=1 ; j<p ; j++){
            int num_of_primes;
            int sum_of_prime = 0;
            MPI_Recv(&num_of_primes, 1,MPI_INT, j, 0, MPI_COMM_WORLD, &status);
            printf("Total number of prime numbers in %d is: %d \n", j, num_of_primes);
            sum_of_prime = sum_of_prime + num_of_primes;
          }

    }
    else{
            int subx, suby;
            int num_of_primes = 0;
            MPI_Recv(&subx, 1, MPI_INT, 0 , 0, MPI_COMM_WORLD, &status);
            MPI_Recv(&suby, 1, MPI_INT, 0 , 0, MPI_COMM_WORLD, &status);

            int i,j;
            int flag =0;
            for(j=0 ; j<suby;++j)
            while(subx <= suby)
            {
                  for (i = 2; i <= subx / 2; ++i) {
                        // condition for non-prime
                        if (subx % i == 0) {
                              flag = 1;
                              break;
                        }
                  }
                  if(flag == 0)
                        num_of_primes = num_of_primes +1;

                  flag =0;
                  subx = subx + 1;
            }
            MPI_Send(&num_of_primes, 1, MPI_INT, 0 , 0, MPI_COMM_WORLD);
    }



    //cleans up the MPI environment and ends MPI communications
    MPI_Finalize();
    return 0;
}
