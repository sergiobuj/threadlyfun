/* @(#)sb_jugador.h
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
