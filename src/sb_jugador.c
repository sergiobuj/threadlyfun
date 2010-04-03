/* @(#)sb_jugador.c
 */


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "sb_dealer.h"
#include "sb_jugador.h"

void *
turno_jugador(void * param)
{
	long num=(long)param;
	cartas[2]=10;
	printf("nombre jugador %ld\ncarta[2]=%d\n",num,cartas[2]);
	return NULL;
}
