#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define THREADS 5
int main()
{
    printf("Hello world!\n");
    printf("Enter the Matrix Length & Width:\n");
    int l, w;
    scanf("%d",&l);
    scanf("%d",&w);
    char arr[l][w];
    char result[w];
    int i, j;
    printf("Enter values for the Matrix:\n");
   for(i=0; i<l ; i++) {
      for(j=0 ; j<w ; j++) {
         scanf("%s", &arr[i][j]);
      }
   }

  /// X O X| X X   X X X| X X
  /// X O X| O X   X X X| X X
  /// O X O| O X   O X O| O X

    int thread_id, size;
    /// Openmp parallel technique
    #pragma omp parallel num_threads(THREADS)
    {
          ///Thread Id
          thread_id = omp_get_thread_num();
          /// Number of Threads
          size = omp_get_num_threads();

          #pragma omp for private(i,j)
          for(i=0; i<l ; i++){
            for(j=0 ; j<w ; j++)
                  result[j] = arr[i][j];
            for(j=0 ; j<w ; j++)
            {
                  if(result[j] == 'o')
                  {
                        if(result[j-1] == result[j+1] &&
                           (result[j-1] != 'o' || result[j+1] != 'o'))
                              result[j] = 'x';
                        arr[i][j] = result[j];
                  }
            }
          }
    }

    for(i=0; i<l ; i++){
      for(j=0 ; j<w ; j++) {
         printf("%c| ", arr[i][j]);
      }
      printf("\n");
    }

    return 0;
}
