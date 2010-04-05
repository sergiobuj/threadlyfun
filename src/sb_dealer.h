/* @(#)sb_dealer.h
   AUTOR: Sergio Botero Uribe
   Creado para la practica de sistemas operativos (Manotazo).
   EAFIT 2010-1
*/

#ifndef _DEALER_H
#define _DEALER_H 1

#define BARAJAS 1
#define PINTAS 4
#define CARTAS_EN_PINTA 13
#define CARTAS 52*BARAJAS
#define NO_CARTA -1


#include <pthread.h>
pthread_t * jugadores;

int cartas[ CARTAS ];
int fin_del_juego;
int num_jugadores;
int cartas_centro;
int carta_siguiente;

void liberar_recursos();
void imprimir_juego();

#endif /* _DEALER_H */
