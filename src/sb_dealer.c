/* @(#)sb_dealer.c
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "sb_dealer.h"
#include "sb_jugador.h"

/* error */
char numero_inv[]="Número de jugadores inválido.\nNúmero debe ser 1 < x < 53\n";
char realloc_error[]="Error al crear espacio para los jugadores\n";
char crear_error[]="Error al crear un jugador\n";
char mutex_error[]="Error al crear los mutex de la ronda\n";

int main(int, char *[]);

void c_baraja(int []);
void barajar_cartas(int [],int);
void lock_mutex_ronda(int);



/*
 */
int main(int argc, char * argv[])
{

  pthread_t * jugadores = NULL;
  int num_jugadores=2, estado_hilo;
  void * estado_join;
  srand((unsigned)time(0));

  if(argc > 1){
    num_jugadores = atoi(argv[1]);
    if( num_jugadores<=2 || num_jugadores>=52 ){
      fprintf(stderr,"%s",numero_inv);
      exit(1);
    }
  }

  void * jugadores_ptr = realloc(jugadores, (num_jugadores*sizeof(pthread_t)));
  if(jugadores_ptr == NULL){
    fprintf(stderr,"%s",realloc_error);
    exit(1);
  }
  jugadores=(pthread_t *)jugadores_ptr;

  void * mtx_jugadores_ptr = realloc(mtx_jugadores, (num_jugadores*sizeof(pthread_mutex_t)));
  if(mtx_jugadores_ptr == NULL){
    fprintf(stderr,"%s",mutex_error);
    free(jugadores);
    exit(1);
  }
  mtx_jugadores=(pthread_mutex_t *)mtx_jugadores_ptr;

  lock_mutex_ronda(num_jugadores);

  long i=0;
  pthread_t *index;
  for(index=jugadores ; index<&jugadores[num_jugadores] ; ++index){
    //    fprintf(stdout,"%ld\n",++i);

    estado_hilo = pthread_create(index,NULL,turno_jugador,(void *)i++);
    if(estado_hilo){
      fprintf(stderr,"%s",crear_error);
      free(jugadores);
      free(mtx_jugadores);
      exit(1);
    }
  }
  
  int join_index;
  for(join_index=0 ; join_index<num_jugadores ; ++join_index){
    pthread_join(jugadores[join_index],&estado_join);
    fprintf(stdout,"Hilo terminado\n");
  }

  realloc(jugadores,0); //cool free(jugadores);
  free(mtx_jugadores);
  return 0;
}



/*
 */
void
c_baraja(int cartas[])
{
	int j,i,k=0;
	for( i=0; i<4*BARAJAS; ++i){
		for( j=0; j<13; ++j){
			cartas[k]=j;
			k++;
		}
	}
}

/*
 */
void
barajar_cartas(int cartas[],int num_cartas)
{
	int i,j;
	for( i=num_cartas-1; i>0; --i){
		j=(arc4random())%(i+1);
		SWAP(cartas[i],cartas[j]);
	}
}


/*
 */
void
lock_mutex_ronda(int index)
{
	while(index){
		--index;
		pthread_mutex_init(&mtx_jugadores[index],NULL);
		pthread_mutex_lock(&mtx_jugadores[index]);
	}
}

