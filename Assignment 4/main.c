#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "mpi.h"

#define THREADS 4

double power(double a, int b)
{
      int i;
      double v=a;
      if(b==1)
            return a;
      for(i=1 ; i<b; i++)
            a = a*v;
      return a;
}

int main(int argc, char *argv[])
{

    int p, rank;
    int n, Mean, i;
    double result, sum;
    MPI_Status status;
    /// initializes the MPI environment
    MPI_Init(&argc, &argv);
    ///find the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    ///find the process id
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0)
    {
          printf("Enter N:");
          scanf("%d", &n);

    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    //#pragma omp parallel num_threads(THREADS)
          #pragma omp parallel for reduction (+: sum) private(i)
          for(i=0; i<n; i++)
          {
                sum += 1.0/power(2, i);
          }

     result=sum;
    //double s = sum;
    MPI_Reduce(&sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
      printf("result: %f \n", result);
      printf("Error: %f \n", result-1.0);
    }

    MPI_Finalize();
    return 0;
}
