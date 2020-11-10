// Lafonction tri-merge
// La fonction tri
// La fonction generator

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define SIZE_BLOC 10
#define NOMBRE_BLOC 10000
#define RANDOM_NOMBRE_MAX 1000

void generator(int* bloc);
void tri(int* bloc, int begin, int end);
void permuter(int *left, int *right);
int min(int* b1, int* b2);
int max(int* b1, int* b2);
void tri_merge();

int main(void) {
  double startTime = omp_get_wtime();

  int bloc[NOMBRE_BLOC][SIZE_BLOC];
  int i = 0;
  int j = 0;
  int omp;

  omp_set_num_threads(4);
  srand( time( NULL ) );
  #pragma omp for
  for (omp = 0; omp < NOMBRE_BLOC; omp++)
  {
    printf("bloc n°%d\n",omp+1 );
    generator(bloc[omp]);
    tri(bloc[omp],0,SIZE_BLOC-1);

  }

  // for (i = 0; i < NOMBRE_BLOC; i++) {
  //   for (j = 0; j < SIZE_BLOC; j++) {
  //     printf("bloc n°%d || bloc[%d] = %d\n",i+1,j+1,bloc[i][j] );
  //   }
  // }

  printf("------------------------\n");

  int tmp;
  printf("NOMBRE_BLOC-1 : %d\n", NOMBRE_BLOC-1);
  for (j = 1; j < NOMBRE_BLOC-1; j++) {
    tmp = 1 + (j % 2);

    printf("------------------------\n");
    printf("tmp : %d\n", tmp);
    printf("omp : %d\n", (NOMBRE_BLOC / 2) - 1);
    printf("------------------------\n");

    #pragma omp for
    for (omp = 0; omp < (4 / 2) - 1; omp++) {
      int minim;
      int maxim;

      printf("------------------------\n");
      printf("b1 %d\n",1 + (tmp + 2 * omp) % NOMBRE_BLOC);
      printf("b2 %d\n",1 + (SIZE_BLOC + 2 * omp + 1) % NOMBRE_BLOC);

      minim = min(bloc[1 + (tmp + 2 * omp) % NOMBRE_BLOC], bloc[1 + (SIZE_BLOC + 2 * omp + 1) % NOMBRE_BLOC]);
      printf("minimum %d\n",minim);
      maxim = max(bloc[1 + (tmp + 2 * omp) % NOMBRE_BLOC], bloc[1 + (SIZE_BLOC + 2 * omp + 1) % NOMBRE_BLOC]);
      printf("maximum %d\n",maxim);

      tri_merge(&bloc[1 + (tmp + 2 * i) % NOMBRE_BLOC], &bloc[1 + (tmp + 2 * i + 1) % NOMBRE_BLOC]);

      printf("\n\n");

    }
  }

  printf("------------------------\n");

  // for (i = 0; i < NOMBRE_BLOC; i++) {
  //   for (j = 0; j < SIZE_BLOC; j++) {
  //     printf("bloc n°%d || bloc[%d] = %d\n",i+1,j+1,bloc[i][j] );
  //   }
  // }

  double stopTime = omp_get_wtime();
  double secsElapsed = stopTime - startTime; // that's all !
  printf("%d\n", secsElapsed);
}

void generator(int* bloc)
{
  int random_value;
  for (int i = 0; i < SIZE_BLOC; i++) {
    // tire un nombre entre 0 et RANDOM_NOMBRE_MAX
    random_value = rand() % RANDOM_NOMBRE_MAX;
    bloc[i] = random_value;
    printf("bloc[%d] : %d\n",i,bloc[i] );
  }
  printf("\n\n\n");
}

void tri(int* bloc,int begin,int end)
{
  int rot;
  int i;
  int j;
  if(begin < end) {
    rot = begin;
    i = begin;
    j = end;
    while (i < j) {
        while(bloc[i] <= bloc[rot] && i < end)
            i++;
        while(bloc[j] > bloc[rot])
            j--;
        if(i < j) {
            permuter(&bloc[i], &bloc[j]);
        }
    }
    permuter(&bloc[rot], &bloc[j]);
    tri(bloc, begin, j - 1);
    tri(bloc, j + 1, end);
  }
}

void permuter(int *left, int *right) {
    int tmp;
    tmp = *left;
    *left = *right;
    *right = tmp;
}

int min(int* b1, int* b2)
{
  int min;
  int i = 0;
  int j = 0;
  while (i < SIZE_BLOC || j < SIZE_BLOC) {
    if (b1[i] > b2[j]) {
      min = b2[j];
      i++;
    }else{
      min = b1[i];
      j++;
    }
  }
  return min;
}

int max(int* b1, int* b2)
{
  int max;
  int i = 0;
  int j = 0;
  while (i < SIZE_BLOC || j < SIZE_BLOC) {
    if (b1[i] < b2[j]) {
      max = b2[j];
      i++;
    }else{
      max = b1[i];
      j++;
    }
  }
  return max;
}


void tri_merge(int* b1, int* b2)
{
  int b[SIZE_BLOC*2];
  int bout1[SIZE_BLOC];
  int bout2[SIZE_BLOC];
  for (int i = 0; i < SIZE_BLOC; i++) {
    b[i]=b1[i];
    b[SIZE_BLOC+i]=b2[i];
  }
  tri(b,0,(SIZE_BLOC*2)-1);
  for (int i = 0; i < SIZE_BLOC; i++) {
    b1[i]=b[i];
    b2[i]=b[SIZE_BLOC+i];
  }
}
