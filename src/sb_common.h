/* @(#)sb_common.h
   AUTOR: Sergio Botero Uribe
   Creado para la practica de sistemas operativos (Manotazo).
   EAFIT 2010-1
*/

#ifndef _COMMON_H
#define _COMMON_H 1

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define BARAJAS 1
#define PINTAS 4
#define CARTAS_EN_PINTA 13
#define NO_CARTA -1
#define CARTAS 52 * BARAJAS

/* Dealer */
int cartas[ CARTAS ];
int cartas_centro;
int carta_siguiente;
int fin_del_juego;
int num_jugadores;

void imprimir_juego();
void liberar_recursos();


/* Jugadores */
pthread_mutex_t *mtx_jugadores;
int **cartas_jugadores;
int * cuenta_cartas;

void * manos(void*);
void init_recursos_jugadores();
void liberar_recursos_jugadores();

#endif /* _COMMON_H */
