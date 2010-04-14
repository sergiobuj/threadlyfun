/* @(#)sb_dealer.h
   AUTOR: Sergio Botero Uribe
   Creado para la practica de sistemas operativos (Manotazo).
   EAFIT 2010-1
*/

#ifndef _DEALER_H
#define _DEALER_H 1
#include "sb_common.h"

/* mensajes */
char fin_juego[] = "Termina ejecución de dealer\n";
char fin_hilos[] = "Número de hilos terminados:";
char primero_jugar[] = "Primero en Jugar:";

/* errores */
char crear_error[] = "Error al crear un jugador\n";


/* funciones */
void comprar_baraja( int [] );
void barajar_cartas( int [], int);
void repartir_cartas();

void poner_jugadores();
void quitar_jugadores();



#endif /* _DEALER_H */
