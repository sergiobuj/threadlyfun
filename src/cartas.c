/* @(#)cartas.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BARAJAS 1
#define PINTAS 4
#define CARTASENPINTA 13
#define CARTAS 52

int **games;

void c_baraja(int cartas[])
{
  int i,j,k=0,l;
  for(l = 0; l < BARAJAS; ++l){
    for( i = 0; i < PINTAS; ++i){
      for( j = 0; j < CARTASENPINTA; ++j){
	cartas[k] = j;
	++k;
      }
    }
  }
}


int main(int argc, char * argv[])
{
  int cartas[CARTAS],  num_jug = 2;
  if(argc > 1) num_jug = atoi( argv[1] );
  void *games_ptr = realloc( games,num_jug * sizeof(int*) );
  if(games_ptr == NULL) exit(1);
  games = games_ptr;
  int i;
  for (i = 0; i < num_jug; ++i){
    games[i] = malloc(sizeof(int) * CARTAS);
    if(games[i] == NULL){
      free( games );
      exit(1);
    }
  }
  
  c_baraja( cartas );
  int j, k ,maxj=0;
  for(j = 0,k = 0; j < CARTAS; ++j){
    for(i = 0; i < num_jug; ++i){
      if(k < CARTAS){
	games[i][j] = cartas[k];
	cartas[k] = -1;
	maxj = (j > maxj)? j : maxj;
      }else{
	games[i][j] = -1;
      }
      ++k;
    }
  }
  
  if( maxj + 2 > CARTAS -1  )
    maxj= CARTAS-1;
  else
    maxj+=2;
  for(j = maxj ; j >= 0 ; --j  ){
    for(i = 0; i < num_jug ; ++i){
      printf("%d\t" , games[i][j] );
    }
    puts("");
  }
  free (games);
  return 0;
}
