/* @(#)sb_jugador.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sb_jugador.h"

void *
turno_jugador(void * param)
{
  printf("nombre jugador %s\n",(char *)param);
  return NULL;
}
