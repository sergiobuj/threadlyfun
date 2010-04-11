/* @(#)sb_main.h
 */

#ifndef _SB_MAIN_H
#define _SB_MAIN_H 1

#include "sb_common.h"

/* mensajes */
char inicio_ronda[] = "Ronda";
char ronda_inicial[] = "==Práctica Manotazo Sistemas Operativos 2010-1\n==Sergio Botero\nRonda inicial";
char ronda_final[] = "Ronda final";
char jugador_string[] = "Jugador";
char cartas_mesa[] = "Cartas en la mesa";
char ganador[] = "Gana el jugador";
char empate[] = "Empataron los jugadores";
char pierden_msg[] = "Perdedor";

/* errores */
char numero_inv[] = "N˙mero de jugadores inv·lido.\nN˙mero debe ser 1 < x < 53\n";
char jugadores_error[] = "Error al crear espacio para los jugadores\n";
char mutex_error[] = "Error al crear los mutex de la ronda\n";
char cartas_error[] = "Error al crear la mesa de juego\n";
char cuenta_error[] = "Error al crear el contador de cartas de cada jugador\n";
char modo_uso[] = "Modo ejecución:\t./dealer 2..52 [h | v]";

/* variables */
char nombre_archivo[] = "resultados";
int vert_hor;

/* funciones */
int main(int, char *[]);
void init_recursos();
void imprimir_juego_v();
void imprimir_juego_h();
void imprimir_resultados();
char valor_carta( int );

#endif /* _SB_MAIN_H */

