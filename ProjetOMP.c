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

void generator(int* bloc, int size_bloc);
void tri(int* bloc, int begin, int end);
void permuter(int *left, int *right);
int min(int* b1, int* b2, int size_bloc);
int max(int* b1, int* b2, int size_bloc);
void tri_merge(int* b1, int* b2,int size_bloc);
float project(int size_bloc, int nb_bloc,int nb_thread);

int main() {
  float tab_times[10];

  tab_times[0] = project(10,100000,4);
  tab_times[1] = project(10,1000,4);

  printf("----\n");

  tab_times[0] = project(10,100000,2);
  tab_times[1] = project(10,1000,2);



  return 0;
}

float project(int size_bloc,int nb_bloc,int nb_thread) {



  struct timespec start, finish;
  double elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);



  int i = 0;
  int j = 0;
  int omp;
  int random_value;

  int** bloc = malloc( sizeof(int*) * nb_bloc);
  for (i = 0; i < nb_bloc; i++) {
    bloc[i] = malloc(sizeof(int) * size_bloc);
    for (j = 0; j < size_bloc; j++)
    {
      random_value = rand() % RANDOM_NOMBRE_MAX;
      bloc[i][j] = random_value;
    }
  }


  omp_set_num_threads(nb_thread);


  srand( time( NULL ) );
  #pragma omp for
  for (omp = 0; omp < nb_bloc; omp++)
  {
    tri(bloc[omp],0,size_bloc-1);
  }



  int tmp;
  for (j = 1; j < nb_bloc-1; j++) {
    tmp = 1 + (j % 2);

    #pragma omp for
    for (omp = 0; omp < (4 / 2) - 1; omp++) {
      int minim;
      int maxim;

      minim = min(bloc[1 + (tmp + 2 * omp) % nb_bloc], bloc[1 + (size_bloc + 2 * omp + 1) % nb_bloc],size_bloc);
      maxim = max(bloc[1 + (tmp + 2 * omp) % nb_bloc], bloc[1 + (size_bloc + 2 * omp + 1) % nb_bloc],size_bloc);
      tri_merge(bloc[1 + (tmp + 2 * i) % nb_bloc], bloc[1 + (size_bloc + 2 * i + 1) % nb_bloc],size_bloc);

    }
  }

  clock_gettime(CLOCK_MONOTONIC, &finish);

  elapsed = (finish.tv_sec - start.tv_sec);
  elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;




  printf("times(s) en fonction de taille total dedonnées (%d*%d) pour nb threads(%d) : %f\n",nb_bloc,size_bloc,4,elapsed);



  // printf("charge : %f\n", elapsed);
  //
  // printf("latence : %f\n", (elapsed/(elapsed)));
  //
  // printf("vitesse d'exécution : %f\n", elapsed);
  // printf("débit : %f\n", elapsed);
  // printf("débit asymptotique : %f\n", elapsed);
  // printf("débit asymptotique : %f\n", elapsed);
  // printf("débit infini : %f\n", elapsed);
  // printf("complexité en temps : %f\n", elapsed);
  // printf("complexité en espace : %f\n", elapsed);


  for ( i = 0; i < nb_bloc; i++) {
    free(bloc[i]);
  }
  free(bloc);


  return elapsed;
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

int min(int* b1, int* b2,int size_bloc)
{
  int min;
  int i = 0;
  int j = 0;
  while (i < size_bloc || j < size_bloc) {
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

int max(int* b1, int* b2,int size_bloc)
{
  int max;
  int i = 0;
  int j = 0;
  while (i < size_bloc || j < size_bloc) {
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


void tri_merge(int* b1, int* b2,int size_bloc)
{
  int b[size_bloc*2];
  int bout1[size_bloc];
  int bout2[size_bloc];
  for (int i = 0; i < size_bloc; i++) {
    b[i]=b1[i];
    b[size_bloc+i]=b2[i];
  }
  tri(b,0,(size_bloc*2)-1);
  for (int i = 0; i < size_bloc; i++) {
    b1[i]=b[i];
    b2[i]=b[size_bloc+i];
  }
}
