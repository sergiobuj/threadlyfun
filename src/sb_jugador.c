/* @(#)sb_jugador.c
 */


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "sb_dealer.h"
#include "sb_jugador.h"

void *
turno_jugador(void * param)
{
  long me=(long)param;
  while(!game_over){

    pthread_mutex_lock(&mtx_jugadores[me]);
    sleep(1);
    if(!game_over){
      printf("Jugando el número: %ld\n",me+1);
    }else{
      break;
     
    }//if
    pthread_mutex_unlock(&mtx_jugadores[SIGUIENTE]); //me #defined
    
  }//while


  return NULL;
}
