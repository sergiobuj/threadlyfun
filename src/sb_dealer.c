/* @(#)sb_dealer.c
 */


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

void init();
void c_baraja(int []);
void barajar_cartas(int [],int);
void lock_mutex_ronda(int);
void iniciar_juego(int);
void poner_jugadores();
void quitar_jugadores();
void liberar_recursos();


/*
 */
int main(int argc, char * argv[])
{
  init();

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

  iniciar_juego( arc4random()%num_jugadores  );

  int time_out=5;
  while(--time_out) sleep(3);
  game_over=1;

  quitar_jugadores(num_jugadores);

  liberar_recursos();

  return 0;
}


/*
 */
void
init()
{
  jugadores = NULL;
  num_jugadores = 2;
  srand((unsigned)time(0));
  game_over=0;

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

/*
 */
void
iniciar_juego(int jugador)
{
  lock_mutex_ronda(num_jugadores);
  c_baraja(cartas);
  barajar_cartas(cartas , CARTAS  );
  poner_jugadores();  
  pthread_mutex_unlock(&mtx_jugadores[jugador] );
}

void
poner_jugadores()
{
  int estado_hilo;
  long i=0;
  pthread_t *index;
  for(index=jugadores ; index<&jugadores[num_jugadores] ; ++index){
    estado_hilo = pthread_create(index,NULL,turno_jugador,(void *)i++);
    if(estado_hilo){
      fprintf(stderr,"%s",crear_error);
      free(jugadores);
      free(mtx_jugadores);
      exit(1);
    }
  }

}

/*
 */
void quitar_jugadores(int index){
  
  while(index)
    pthread_mutex_unlock(&mtx_jugadores[--index]);

  void * estado_join;
  int join_index;
  for(join_index=0 ; join_index<num_jugadores ; ++join_index){
    pthread_join(jugadores[join_index],&estado_join);
    fprintf(stdout,"Hilo terminado\n");
  }
}


/*
 */
void
liberar_recursos()
{
  realloc(jugadores,0); //cool free(jugadores);
  free(mtx_jugadores);
}
