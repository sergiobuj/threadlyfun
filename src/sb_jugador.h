/* @(#)sb_jugador.h
   AUTOR: Sergio Botero Uribe
   Creado para la practica de sistemas operativos (Manotazo).
   EAFIT 2010-1
*/

#ifndef _JUGADOR_H
#define _JUGADOR_H 1

#define SIGUIENTE ((me+1)%num_jugadores)

#include <pthread.h>
pthread_mutex_t *mtx_jugadores;
int **cartas_jugadores;
int * cuenta_cartas;

void * manos(void *);
#endif /* _JUGADOR_H */
