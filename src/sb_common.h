/* @(#)sb_common.h
   AUTOR: Sergio Botero Uribe
   Creado para la practica de sistemas operativos (Manotazo).
   EAFIT 2010-1
*/

#ifndef _COMMON_H
#define _COMMON_H 1
/*
#ifndef __APPLE__
#include <sys/types.h>
#include <sys/user.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#endif
*/
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>

#define BARAJAS 1
#define PINTAS 4
#define CARTAS_EN_PINTA 13
#define NO_CARTA -1
#define CARTAS 52 * BARAJAS
#define MILLISEG_MAX 500


/* main */
int fin_del_juego;
int num_jugadores;
int jugador_especifico;

pthread_t * jugadores;

int random_port( int );
void imprimir_juego();
void liberar_recursos();

/* Dealer */
int cartas[ CARTAS ];
int cartas_centro;
int carta_siguiente;

pthread_mutex_t mtx_juego;
pthread_cond_t cond_fin_juego;

void iniciar_juego();
void terminar_juego();

/* Jugadores */
int **cartas_jugadores;
int * cuenta_cartas;

pthread_mutex_t *mtx_jugadores;

void * manos( void* );
void init_recursos_jugadores();
void liberar_recursos_jugadores();

#endif /* _COMMON_H */
