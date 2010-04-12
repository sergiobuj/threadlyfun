/* @(#)sb_dealer.c
   AUTOR: Sergio Botero Uribe
   Creado para la practica de sistemas operativos (Manotazo).
   EAFIT 2010-1
*/

#include "sb_dealer.h"


/*
 */
void comprar_baraja(int cartas[]) {
  int i , j , k = 0 , l;
  for(l = 0; l < BARAJAS; ++l){
    for(i = 0; i < PINTAS; ++i){
      for(j = 0; j < CARTAS_EN_PINTA; ++j){
	cartas[k] = j;
	++k;
      }
    }
  }
}


/*
  Método de R.A. Fisher and F. Yates, Explicado en `The Art of Computer programming' by Donald Knuth
*/
void barajar_cartas(int cartas[],int num_cartas) {
  int i,j,aux;
  for( i = num_cartas -1; i > 0; --i){
    j = random_port( (i + 1) );
    aux = cartas[i];
    cartas[i] = cartas[j];
    cartas[j] = aux;
  }
}


/*
 */
void repartir_cartas() {
  int i, j, k, l, primero_recibir;
  for(i = 0; i < CARTAS ; ++i) cuenta_cartas[i] = 0;
  
  if( jugador_especifico == -1)
    primero_recibir = random_port( num_jugadores );
  else if( jugador_especifico == 0)
    primero_recibir = 0;
  else if( jugador_especifico )
    primero_recibir = jugador_especifico - 1 ;
  else
    primero_recibir = 0;

  for(j = 0,k = 0; j < CARTAS; ++j){
    for(l = 0; l < num_jugadores; ++l){
      i = (primero_recibir + l )%num_jugadores;
			
      if(k < CARTAS){
	cartas_jugadores[i][j] = cartas[k];
	cartas[k] = NO_CARTA;
	++cuenta_cartas[i];
      }else{
	cartas_jugadores[i][j] = NO_CARTA;
      }
      ++k;
    }
  }
}


/*
 */
void iniciar_juego(int jugador) {
  init_recursos_jugadores();
	
	
  int index = num_jugadores;
  while(index){
    --index;
    pthread_mutex_init( &mtx_jugadores[index] , NULL);
    pthread_mutex_lock( &mtx_jugadores[index] );
  }
	
	
  comprar_baraja( cartas );
  barajar_cartas( cartas , CARTAS  );
  repartir_cartas();
  imprimir_juego( 0 );
  poner_jugadores();
  pthread_mutex_unlock( &mtx_jugadores[jugador] );
}



/*
 */
void terminar_juego() {
  imprimir_juego( -1 );
  quitar_jugadores( num_jugadores );
  fprintf(stdout, "%s" , fin_juego);
}


/*
 */
void poner_jugadores() {
  int estado_hilo;
  long i = 0;
  pthread_t *index;
  for(index = jugadores ; index < &jugadores[num_jugadores] ; ++index){
    estado_hilo = pthread_create( index , NULL, manos ,(void*) i++);
    if( estado_hilo ){
      fprintf(stderr , "%s" , crear_error);
      free( jugadores );
      free( mtx_jugadores );
      exit( EXIT_FAILURE );
    }
  }
}


/*
 */
void quitar_jugadores(int index) {
  int i = index;
  while( index )
    pthread_mutex_unlock( &mtx_jugadores[--index] );
	
  void * estado_join;
  int join_index;
  for(join_index = 0 ; join_index < num_jugadores ; ++join_index){
    pthread_join( jugadores[join_index], &estado_join );
  }
  fprintf(stdout, "\n%s\t%d\n", fin_hilos, join_index );
	
  while( i ) pthread_mutex_destroy( &mtx_jugadores[--i] );
	
}

