/* @(#)sb_dealer.h
   AUTOR: Sergio Botero Uribe
   Creado para la practica de sistemas operativos (Manotazo).
   EAFIT 2010-1
*/

#ifndef _DEALER_H
#define _DEALER_H 1
#include "sb_common.h"

pthread_t * jugadores;

/* error */
char numero_inv[]="Número de jugadores inválido.\nNúmero debe ser 1 < x < 53\n";
char jugadores_error[]="Error al crear espacio para los jugadores\n";
char crear_error[]="Error al crear un jugador\n";
char mutex_error[]="Error al crear los mutex de la ronda\n";
char cartas_error[]="Error al crear la mesa de juego\n";
char cuenta_error[]="Error al crear el contador de cartas de cada jugador\n";

/* mensaje */
char fin_juego[]="Termina ejecución de dealer\n";
char fin_hilos[]="Nómero de hilos terminados:";
char inicio_ronda[]="Ronda";
char ronda_inicial[]="Ronda inicial";
char ronda_final[]="Ronda final";
char jugador_string[]="Jugador";
char cartas_mesa[]="Cartas en la mesa";

int main(int, char *[]);

void init();
void c_baraja(int []);
void barajar_cartas(int [],int);
void repartir_cartas();
void lock_mutex_ronda(int);
void iniciar_juego();
void poner_jugadores();
void quitar_jugadores();
void terminar_juego();

#endif /* _DEALER_H */
