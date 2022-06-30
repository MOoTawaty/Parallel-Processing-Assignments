#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "mpi.h"


// Returns floor of square root of x
int floorSqrt(int x)
{
    // Base cases
    if (x == 0 || x == 1)
    return x;

    // Staring from 1, try all numbers until
    // i*i is greater than or equal to x.
    int i = 1, result = 1;
    while (result <= x)
    {
      i++;
      result = i * i;
    }
    return i - 1;
}


int main(int argc, char *argv[])
{
    int p, rank;
    int n, Mean, result, i, sum, SD;
    MPI_Status status;
    /// initializes the MPI environment
    MPI_Init(&argc, &argv);
    ///find the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    ///find the process id
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    ///For random generator
    srand(time(0));

    /// Array of the original set
    int* arr1 ;

    /// Array of the squared differences set
    int* arr2 ;

    /** Master process */
    if(rank == 0)
    {
          printf("Hello Master!\n");
          ///the integer n (number of elements per each process)
          printf("Enter number of elements: \n");
          scanf("%d", &n);

          arr1 = malloc((n*p)* sizeof(int));
          arr2 = malloc((n*p)* sizeof(int));

           sum = 0;
          for(i=0 ; i<n*p ; i++)
          {
                /** Felling the arr with random numbers <= 100 */
                arr1[i] = (rand() % 20);
                sum += arr1[i];
          }

           /// Calculating Mean
            Mean = sum/(n*p);

           int s;
          for(i=0 ; i<n*p ; i++)
          {
                /** for each value, subtract the mean and square the result */
                s = (arr1[i] - Mean);
                arr2[i] = s * s;
                SD += arr2[i];
          }
    }

    MPI_Bcast(&SD, 1, MPI_INT, 0, MPI_COMM_WORLD);
    SD /= n*p;
    MPI_Reduce(&SD, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);


    if(rank == 0)
    {
          printf("Mean: %d \n", Mean);
          for(i=0 ; i<n*p ; i++)
          {
                printf("%d :: %d \n", arr1[i],arr2[i]);
          }
          printf("Standard Deviation: %d \n", floorSqrt(result));
    }



    //cleans up the MPI environment and ends MPI communications
    MPI_Finalize();
    return 0;
}
