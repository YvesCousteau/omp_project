// Lafonction tri-merge
// La fonction tri
// La fonction generator

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define SIZE_BLOC 10
#define NOMBRE_BLOC 3
#define RANDOM_NOMBRE_MAX 1000

void generator(int* bloc);
void tri(int* bloc, int begin, int end);
void permuter(int *left, int *right);
void min(int* b1, int* b2);
void max(int* b1, int* b2);
void tri_merge();

int main(void) {
  int bloc[NOMBRE_BLOC][SIZE_BLOC];
  int i = 0;
  int j = 0
  int omp;
  omp_set_num_threads(NOMBRE_BLOC);
  srand( time( NULL ) );
  #pragma omp parallel
  {
    omp = omp_get_thread_num();
    printf("bloc n°\n",omp+1 );
    generator(bloc[omp]);
    tri(bloc[omp],0,SIZE_BLOC-1);
  }
  tmp = SIZE_BLOC;
  for (j = 1; j < NOMBRE_BLOC-1; j++) {
    tmp = 1 + (j % 2);
    omp_set_num_threads((NOMBRE_BLOC / 2) - 1);
    #pragma omp parallel
    {
      omp = omp_get_thread_num();
      b1 = bloc[1 + (tmp + 2 * i) % NOMBRE_BLOC];
      b2 = bloc[1 + (tmp + 2 * i + 1) % NOMBRE_BLOC];
      min = min(b1, b2);
      printf("minimum %d\n",min);
      max = max(b1, b2);
      printf("maximum %d\n",max);
      tri_merge(b1, b2);

      for (i = 0; i < count; i++) {
        printf("n°%d || bout1 %d || bout2 %d || omp n°%d \n",i+1,b1[i],b2[i],omp);
      }
      printf("\n\n\n");
    }
  }
}

void generator(int* bloc)
{
  int random_value;
  printf("\n");

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
        while(tab[i] <= tab[rot] && i < end)
            i++;
        while(tab[j] > tab[rot])
            j--;
        if(i < j) {
            permuter(&tab[i], &tab[j]);
        }
    }
    permuter(&tab[rot], &tab[j]);
    tri(tab, begin, j - 1);
    tri(tab, j + 1, end);
  }
}

void permuter(int *left, int *right) {
    int switch;
    switch = *left;
    *left = *right;
    *right = switch;
}

void min(int* b1, int* b2)
{
  int min;
  for (int i = 0; i < SIZE_BLOC; i++) {
    for (int j = 0; j < count; j++) {
      if (b1[i] > b2[j]) {
        min = b2[j];
        i++
      }else{
        min = b1[i];
        j++
      }
    }
  }
}

void max(int* b1, int* b2)
{
  int max;
  for (int i = 0; i < SIZE_BLOC; i++) {
    for (int j = 0; j < count; j++) {
      if (b1[i] < b2[j]) {
        max = b2[j];
        i++
      }else{
        max = b1[i];
        j++
      }
    }
  }
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
  for (i = 0; i < SIZE_BLOC; i++) {
    b1[i]=b[i];
    b2[i]=b[SIZE_BLOC+i];
  }
}
