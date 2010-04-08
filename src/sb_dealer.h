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
char numero_inv[] = "Número de jugadores inválido.\nNúmero debe ser 1 < x < 53\n";
char jugadores_error[] = "Error al crear espacio para los jugadores\n";
char crear_error[] = "Error al crear un jugador\n";
char mutex_error[] = "Error al crear los mutex de la ronda\n";
char cartas_error[] = "Error al crear la mesa de juego\n";
char cuenta_error[] = "Error al crear el contador de cartas de cada jugador\n";
char modo_uso[] = "Modo ejecuci—n:\t./dealer 2..52 [h | v]";

/* mensaje */
char fin_juego[] = "Termina ejecución de dealer\n";
char fin_hilos[] = "Número de hilos terminados:";
char inicio_ronda[] = "Ronda";
char ronda_inicial[] = "==Pr‡ctica Manotazo Sistemas Operativos 2010-1\n==Sergio Botero\nRonda inicial";
char ronda_final[] = "Ronda final";
char jugador_string[] = "Jugador";
char cartas_mesa[] = "Cartas en la mesa";
char ganador[] = "Gana el jugador";
char empate[] = "Empataron los jugadores";
char pierden_msg[] = "Perdedor";

char nombre_archivo[] = "resultados";

int main(int, char *[]);
int vert_hor;

void init();
void c_baraja(int []);
void barajar_cartas(int [],int);
void repartir_cartas();
void lock_mutex_ronda(int);
void iniciar_juego();
void poner_jugadores();
void quitar_jugadores();
void terminar_juego();
char valor_carta(int);
void imprimir_juego_v();
void imprimir_juego_h();
void imprimir_resultados();

#endif /* _DEALER_H */
