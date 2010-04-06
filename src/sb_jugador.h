/* @(#)sb_jugador.h
   AUTOR: Sergio Botero Uribe
   Creado para la practica de sistemas operativos (Manotazo).
   EAFIT 2010-1
*/

#ifndef _JUGADOR_H
#define _JUGADOR_H 1

#include "sb_common.h"

#define SIGUIENTE (( me + 1 ) % num_jugadores)

/* error */
char crear_ojos_error[] = "Error al crear los ojos de algún jugador\n";

/* mensajes */
char jugador_pierde[] = "\nEsta ronda la pierde el jugador";

int ronda_jugada;
int poner_manos;
int quitar_manos;
int cartas_recogidas;
int manos_en_centro;
pthread_mutex_t manotazo;
pthread_mutex_t poner_mano;
pthread_mutex_t quitar_mano;

void * tomar_cartas( long );
void * ojos( void *);
void forzar_salida();

#endif /* _JUGADOR_H */
