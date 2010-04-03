/* @(#)sb_jugador.h
 */

#ifndef _JUGADOR_H
#define _JUGADOR_H 1

#include <pthread.h>

pthread_mutex_t *mtx_jugadores;

void * turno_jugador(void *);
#endif /* _JUGADOR_H */
