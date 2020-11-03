// Lafonction tri-merge
// La fonction tri
// La fonction generator

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define TAILLE_BLOC 10
#define NOMBRE_BLOC 3
#define RANDOM_NOMBRE_MAX 1000

void generator();
void tri();
void tri_merge();

int main(void) {

  int bloc[NOMBRE_BLOC][TAILLE_BLOC];
  int  i = 0;

  omp_set_num_threads(NOMBRE_BLOC);
  srand( time( NULL ) );

  #pragma omp parallel
  {
    int j;
    i = omp_get_thread_num();

    printf("bloc[%d]\n",i );
    generator(bloc[i]);
  }
}

void generator(int* bloc)
{
  int random_value;
  printf("\n\n\n");

  for (int i = 0; i < TAILLE_BLOC; i++) {
    // tire un nombre entre 0 et RANDOM_NOMBRE_MAX
    random_value = rand() % RANDOM_NOMBRE_MAX;
    bloc[i] = random_value;
    printf("bloc[%d] : %d\n",i,bloc[i] );
  }
  printf("\n\n\n");
}

void tri_merge()
{

}

void tri()
{

}
