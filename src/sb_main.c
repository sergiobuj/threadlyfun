/* @(#)sb_main.c
   AUTOR: Sergio Botero Uribe
   Creado para la practica de sistemas operativos (Manotazo).
   EAFIT 2010-1
*/

#include "sb_main.h"


/*
 */
int main(int argc, char * argv[])
{
  vert_hor = 0;
  jugador_especifico = 0;


  if(argc > 1){
    num_jugadores = atoi(argv[1]);
    if( num_jugadores < 2 || num_jugadores > 52 ){
      fprintf(stderr, "%s" , numero_inv );
      exit( EXIT_FAILURE );
    }
  }

  char opt;
  while( (opt = getopt(argc - 1, &argv[1], "vj::")) != -1  ){
    switch( opt ){
    case 'v':
      vert_hor = 1;
      break;
    case 'j':
      if(optarg){
	if( atoi(optarg) > 0 && atoi(optarg) <= num_jugadores ){
	  jugador_especifico = atoi(optarg);
	}else{
	  fprintf(stderr, "%s%d\n", jug_esp_err, num_jugadores);
	  exit( EXIT_FAILURE );
	}
      }else{
	jugador_especifico = -1;
      }
      break;
    case '?':
      fprintf(stderr, "%s",modo_uso);
      exit( EXIT_FAILURE );
    }
  }

  init_recursos();
  iniciar_juego( random_port( num_jugadores ) );
	
  pthread_mutex_lock( &mtx_juego );
  while( !fin_del_juego ) pthread_cond_wait( &cond_fin_juego , &mtx_juego ) ;
  pthread_mutex_unlock( &mtx_juego );
	
  terminar_juego();
  liberar_recursos();
	
  return 0;
}


/*
 */
void init_recursos() {
	
  freopen( nombre_archivo, "w", stdout);
  srand( (unsigned)time(0) );
	
#ifdef __APPLE__
  //puts("I'm darwin");
#endif
	
  fin_del_juego = 0;
  carta_siguiente = NO_CARTA;
	
  pthread_mutex_init( &mtx_juego , NULL);
  pthread_cond_init( &cond_fin_juego , NULL );
	
  jugadores = NULL;
  cartas_jugadores = NULL;
  mtx_jugadores = NULL;
  cuenta_cartas = NULL;
		
  void * jugadores_ptr = realloc( jugadores, ( num_jugadores * sizeof(pthread_t) ));
  if(jugadores_ptr == NULL){
    fprintf(stderr , "%s" , jugadores_error);
    exit( EXIT_FAILURE );  }
  jugadores = (pthread_t*) jugadores_ptr;
	
  void * cartas_jugadores_ptr = realloc( cartas_jugadores , num_jugadores * sizeof(int *) );
  if(cartas_jugadores_ptr == NULL){
    fprintf(stderr , "%s" , cartas_error);
    free( jugadores );
    exit( EXIT_FAILURE );  }
  cartas_jugadores = cartas_jugadores_ptr;
  int i;
  for (i = 0; i < num_jugadores ; ++i){
    cartas_jugadores[i] = malloc( sizeof(int) * CARTAS );
    if(cartas_jugadores[i] == NULL){
      free( jugadores );
      free( cartas_jugadores );
      exit( EXIT_FAILURE );
    }
  }
	
  void * mtx_jugadores_ptr = realloc( mtx_jugadores, (num_jugadores * sizeof(pthread_mutex_t) ));
  if(mtx_jugadores_ptr == NULL){
    fprintf(stderr , "%s" , mutex_error);
    free( jugadores );
    free( cartas_jugadores );
    exit( EXIT_FAILURE );
  }
  mtx_jugadores = (pthread_mutex_t*) mtx_jugadores_ptr;
	
  void * cuenta_cartas_ptr = realloc(cuenta_cartas, (num_jugadores * sizeof(int) ));
  if(cuenta_cartas_ptr == NULL){
    fprintf(stderr,"%s",cuenta_error);
    free(jugadores);
    free(cartas_jugadores);
    free(mtx_jugadores);
    exit( EXIT_FAILURE );
  }
  cuenta_cartas = (int *)cuenta_cartas_ptr;


}



/*
 */
void imprimir_resultados() {
  char ganan[52] = "", pierden[52] = "";
  int i, count_g = 0 , count_p = 0 , max_p = 0;
	
  for(i = 0; i < num_jugadores; ++i){
    if( cuenta_cartas[i] == 0){
      ++count_g;
    }else if( cuenta_cartas[i] == max_p ){
      ++count_p;
    }else if( max_p < cuenta_cartas[i] ){
      max_p = cuenta_cartas[i];
      count_p = 1;
    }
  }
  for(i = 0; i < num_jugadores; ++i){
    if( cuenta_cartas[i] == 0  ){
      sprintf(ganan,"%s %d",ganan, i + 1 );
    }else if(cuenta_cartas[i] == max_p){
      sprintf(pierden,"%s %d",pierden, i + 1 );
    }
  }
	
	
  if( count_g > 1 ){
    fprintf(stdout, "%s %s\n",empate,ganan);
  }else if( count_g == 1 ){
    fprintf(stdout, "%s %s\n",ganador,ganan);
  }
	
  if( count_p > 1 ){
    fprintf(stdout, "%ses %s\n",pierden_msg,pierden);
  }else if( count_p == 1 ){
    fprintf(stdout, "%s %s\n",pierden_msg,pierden);
  }
  puts("");
	
}

/*
 */
void imprimir_juego_v() {
  int i, j, k, karta, maxj = 0;
	
  for(i = 0 ; i < num_jugadores; ++i)
    if (cuenta_cartas[i] > maxj) {
      maxj = cuenta_cartas[i];
    }
	
  if( maxj == CARTAS ) maxj = CARTAS-1;
	
  for(j = maxj ; j >= 0 ; --j  ){
    printf("|\t");
    for(i = 0; i < num_jugadores ; ++i){
      karta = cartas_jugadores[i][j];
      printf("%c\t" ,  valor_carta(karta) );
    }
    puts("");
  }
	
  printf("|\t");
  for(i = 0; i < num_jugadores ; ++i) printf("(%d)\t",cuenta_cartas[i]);
  puts("");
  printf("|\t");
  for(i = 0; i < num_jugadores ; ++i) printf("J#%d\t",i+1);
  puts("");
	
}


/*
 */
void imprimir_juego_h() {
  int i, j, karta;	
	
  for(i = 0; i < num_jugadores; ++i){
    for(j = 0; j < CARTAS; ++j){
      if(j == 0 ) fprintf(stdout,"%s #%3d  (%d)\n", jugador_string, i + 1 , cuenta_cartas[i]);
      karta = cartas_jugadores[i][j];
      if(karta == NO_CARTA){
	break;
      }
      fprintf(stdout,"%c  ",  valor_carta(karta));
    }
    puts("");
  }	
}


/*
 */
char valor_carta(int karta){
  char rep_carta;
	
  if(karta == 0){
    rep_carta='A';
  }else if(karta == 9){
    rep_carta= 'X';
  }else if(karta == 10){
    rep_carta = 'J';
  }else if(karta == 11){
    rep_carta = 'Q';
  }else if(karta == 12){
    rep_carta = 'K';
  }else if(karta == -1){
    rep_carta = ' ';
  }else{
    rep_carta = '1' + karta;
  }
	
  return rep_carta;
}




/*
 */
void imprimir_juego(int ronda) {
	
  if(ronda == -1)
    fprintf( stdout, "\n\t--------------------\n\n\n%s\n", ronda_final);
  else if (ronda == 0)
    fprintf( stdout, "%s\n",ronda_inicial);
  else 
    fprintf( stdout, "\n\t--------------------\n\n\n%s %d\n", inicio_ronda, ronda);
	
  if(vert_hor == 1)
    imprimir_juego_v( ) ;		
  else
    imprimir_juego_h( ) ;
	
  int i,j,karta;
  for(j = 0; j < CARTAS; ++j){
    if( j == 0 ) fprintf(stdout,"%s (%d)\n", cartas_mesa , cartas_centro);
    karta = cartas[j];
    if(karta == NO_CARTA){
      break;
    }
    fprintf(stdout,"%c  ", valor_carta(karta));
  }
  puts("");
	
  if(ronda == -1) imprimir_resultados();
}


/*
 */
void liberar_recursos(){
  liberar_recursos_jugadores();
	
  pthread_mutex_destroy( &mtx_juego);
  pthread_cond_destroy( &cond_fin_juego);
	
  free( jugadores );
  free( cartas_jugadores );
	
#ifdef __APPLE__
  //puts("I'm darwin and I free");
  free( mtx_jugadores );
  free( cuenta_cartas );
#endif
	
}


/*
 */
int random_port( int rand_max){

#ifdef __APPLE__
  //puts("I'm darwin and I'm random");
  return arc4random()%rand_max;

#else
  return random()%rand_max;

#endif


}



