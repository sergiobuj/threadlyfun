/* @(#)sb_jugador.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "sb_dealer.h"
#include "sb_jugador.h"

/*
 */
void *
manos(void * param)
{
  long me=(long)param;
  while(!fin_del_juego){

    pthread_mutex_lock(&mtx_jugadores[me]);

    if(!fin_del_juego){
      if(cuenta_cartas[me]){
	carta_siguiente = (carta_siguiente+1) % CARTAS_EN_PINTA;
	cartas[cartas_centro] = cartas_jugadores[me][cuenta_cartas[me]-1];
	++cartas_centro;
	cartas_jugadores[me][cuenta_cartas[me]-1] = NO_CARTA;
	--cuenta_cartas[me];
	//	printf("Jugando el número: %ld\n",me+1);
      }

    }else{
      break;
    }//if
    pthread_mutex_unlock(&mtx_jugadores[SIGUIENTE]); //me #defined
    
  }//while
  return NULL;
}


/*
 */
void *
ojos(int me)
{

}

/*
 */
void *
tomar_cartas(int me)
{
  int mazo_aux[CARTAS], i;
  for(i=0; i<CARTAS ;++i) mazo_aux[i]=NO_CARTA;
  for(i=0; i<cartas_centro; ++i){
    mazo_aux[i] = cartas[i];
    cartas[i]=NO_CARTA;
  }
  for(i=0 ;i<cuenta_cartas[me]; ++i)
    mazo_aux[cartas_centro + i] = cartas_jugadores[me][i];
  
  cuenta_cartas[me]+= cartas_centro;
  cartas_centro=0;
  
  for(i=0; i<cuenta_cartas[me]; ++i)
    cartas_jugadores[me][i] = mazo_aux[i];
  
  return NULL;
}
