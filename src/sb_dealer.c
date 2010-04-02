/* @(#)sb_dealer.c
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "sb_dealer.h"
#include "sb_jugador.h"

int main(int argc, char * argv[])
{
  pthread_t * jugadores = NULL;
  int num_jugadores=2, estado_hilo;
  void * estado_join;
  srand((unsigned)time(0));

  if(argc > 1){
    num_jugadores = atoi(argv[1]);
    if( num_jugadores<=2 || num_jugadores>=52 ){
      fprintf(stderr,"%s",numero_inv);
      exit(1);
    }
  }

  void * jugadores_ptr = realloc(jugadores, (num_jugadores*sizeof(pthread_t)));
  if(jugadores_ptr == NULL){
    fprintf(stderr,"%s",realloc_error);
    exit(1);
  }
  jugadores=(pthread_t *)jugadores_ptr;

  int i=0;
  pthread_t *index;
  for(index=jugadores ; index<&jugadores[num_jugadores] ; ++index){
    fprintf(stdout,"%d\n",++i);
    char * nombre = nomi[arc4random()%5];
    estado_hilo = pthread_create(index,NULL,turno_jugador,(void *)nombre);
    if(estado_hilo){
      fprintf(stderr,"%s",crear_error);
      free(jugadores);
      exit(1);
    }
  }
  
  int join_index;
  for(join_index=0 ; join_index<num_jugadores ; ++join_index){
    pthread_join(jugadores[join_index],&estado_join);
    fprintf(stdout,"Hilo terminado\n");
  }
  realloc(jugadores,0);
  return 0;
}
