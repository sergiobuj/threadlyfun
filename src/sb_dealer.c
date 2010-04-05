/* @(#)sb_dealer.c
   AUTOR: Sergio Botero Uribe
   Creado para la practica de sistemas operativos (Manotazo).
   EAFIT 2010-1
*/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "sb_dealer.h"
#include "sb_jugador.h"

/* error */
char numero_inv[]="Número de jugadores inválido.\nNúmero debe ser 1 < x < 53\n";
char jugadores_error[]="Error al crear espacio para los jugadores\n";
char crear_error[]="Error al crear un jugador\n";
char mutex_error[]="Error al crear los mutex de la ronda\n";
char cartas_error[]="Error al crear la mesa de juego\n";
char cuenta_error[]="Error al crear el contador de cartas de cada jugador\n";

/* mensaje */
char fin_juego[]="Termina ejecución de dealer\n";
char fin_hilos[]="Número de hilos terminados:";
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
/*
 */
int main(int argc, char * argv[])
{
  init();

  if(argc > 1){
    num_jugadores = atoi(argv[1]);
    if( num_jugadores<2 || num_jugadores>52 ){
      fprintf(stderr,"%s",numero_inv);
      exit(1);
    }
  }
  
  void * jugadores_ptr = realloc(jugadores, (num_jugadores*sizeof(pthread_t)));
  if(jugadores_ptr == NULL){
    fprintf(stderr,"%s",jugadores_error);
    exit(1);
  }
  jugadores=(pthread_t *)jugadores_ptr;

  void *cartas_jugadores_ptr = realloc(cartas_jugadores , num_jugadores * sizeof(int *));
  if(cartas_jugadores_ptr == NULL){
    fprintf(stderr,"%s",cartas_error);
    free(jugadores);
    exit(1);
  }
  cartas_jugadores = cartas_jugadores_ptr;
  int i;
  for (i = 0; i < num_jugadores ; ++i){
    cartas_jugadores[i] = malloc(sizeof(int) * CARTAS);
    if(cartas_jugadores[i]==NULL){
      free(jugadores);
      free(cartas_jugadores);
      exit(1);
    }
  }

  void * mtx_jugadores_ptr = realloc(mtx_jugadores, (num_jugadores*sizeof(pthread_mutex_t)));
  if(mtx_jugadores_ptr == NULL){
    fprintf(stderr,"%s",mutex_error);
    free(jugadores);
    free(cartas_jugadores);
    exit(1);
  }
  mtx_jugadores=(pthread_mutex_t *)mtx_jugadores_ptr;
  
  void * cuenta_cartas_ptr = realloc(cuenta_cartas, (num_jugadores*sizeof(int)));
  if(cuenta_cartas_ptr == NULL){
    fprintf(stderr,"%s",cuenta_error);
    free(jugadores);
    free(cartas_jugadores);
    free(mtx_jugadores);
    exit(1);
  }
  cuenta_cartas = (int *)cuenta_cartas_ptr;

  iniciar_juego( arc4random()%num_jugadores  );

  while(!fin_del_juego);
  terminar_juego();
  return 0;
}


/*
 */
void
init()
{
  freopen("Resultados","w",stdout);

  jugadores = NULL;
  num_jugadores = 2;
  srand((unsigned)time(0));
  fin_del_juego=0;
  carta_siguiente = NO_CARTA;
}

/*
 */
void
c_baraja(int cartas[])
{
  int i,j,k=0,l;
  for(l=0; l<BARAJAS; ++l){
    for( i=0; i<PINTAS; ++i){
      for( j=0; j<CARTAS_EN_PINTA; ++j){
	cartas[k]=j;
	k++;
      }
    }
  }
}

/*
  Método de R.A. Fisher and F. Yates, Explicado en `The Art of Computer programming' by Donald Knuth
*/
void
barajar_cartas(int cartas[],int num_cartas)
{
  int i,j,aux;
  for( i=num_cartas-1; i>0; --i){
    j=(arc4random())%(i+1);
    aux = cartas[i];
    cartas[i] = cartas[j];
    cartas[j]=aux;
  }
}


/*
 */
void
repartir_cartas()
{  
  int i,j,k;
  for(i=0; i<CARTAS ;++i) cuenta_cartas[i]=0;

  for(j=0,k=0; j<CARTAS; ++j){
    for(i=0; i<num_jugadores; ++i){
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
  init_recursos_jugadores();
  lock_mutex_ronda(num_jugadores);
  c_baraja(cartas);
  barajar_cartas(cartas , CARTAS  );
  repartir_cartas(cartas_jugadores);
  imprimir_juego(0);
  poner_jugadores();  
  pthread_mutex_unlock(&mtx_jugadores[jugador] );
}


/*
 */
void
poner_jugadores()
{
  int estado_hilo;
  long i=0;
  pthread_t *index;
  for(index=jugadores ; index<&jugadores[num_jugadores] ; ++index){
    estado_hilo = pthread_create(index,NULL, manos ,(void *)i++);
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
void
quitar_jugadores(int index)
{ 
  int i=index;
  while(index)
    pthread_mutex_unlock(&mtx_jugadores[--index]);
  
  void * estado_join;
  int join_index;
  for(join_index=0 ; join_index<num_jugadores ; ++join_index){
    pthread_join(jugadores[join_index],&estado_join);
  }
  fprintf(stdout,"\n%s\t%d\n",fin_hilos,join_index);

  while(i)
    pthread_mutex_destroy(&mtx_jugadores[--i]);

}


/*
 */
void
liberar_recursos()
{
  liberar_recursos_jugadores();
  realloc(jugadores,0); //cool free(jugadores);
  free(cartas_jugadores);
  free(mtx_jugadores);
  free(cuenta_cartas);
}


/*
 */
void
imprimir_juego(int ronda)
{
	

	
  int i,j,karta;
  char rep_carta;
  if(ronda == -1)
    fprintf( stdout, "\n\t--------------------\n\n\n%s\n",ronda_final,ronda);
  else if (ronda == 0)
    fprintf( stdout, "%s\n",ronda_inicial);
  else 
    fprintf( stdout, "\n\t--------------------\n\n\n%s %d\n",inicio_ronda,ronda);
	
  for(i=0; i<num_jugadores; ++i){
    for(j=0; j<CARTAS; ++j){
      if(j==0) fprintf(stdout,"%s #%3d  (%d)\n",jugador_string,i+1,cuenta_cartas[i]);
      karta = cartas_jugadores[i][j];
      if(karta == NO_CARTA){
	break;
      }else if(karta == 0){
	rep_carta='A';
      }else if(karta == 9){
	rep_carta= 'X';
      }else if(karta == 10){
	rep_carta = 'J';
      }else if(karta == 11){
	rep_carta = 'Q';
      }else if(karta == 12){
	rep_carta = 'K';
      }else{
	rep_carta = '1'+karta;
      }
      fprintf(stdout,"%c  ", rep_carta);
    }
    puts("");
  }
	
  for(j=0; j<CARTAS; ++j){
    if(j==0) fprintf(stdout,"%s (%d)\n",cartas_mesa,cartas_centro);
    karta = cartas[j];
    if(karta == NO_CARTA){
      break;
    }else if(karta == 0){
      rep_carta='A';
    }else if(karta == 9){
      rep_carta= 'X';
    }else if(karta == 10){
      rep_carta = 'J';
    }else if(karta == 11){
      rep_carta = 'Q';
    }else if(karta == 12){
      rep_carta = 'K';
    }else{
      rep_carta = '1'+karta;
    }
    fprintf(stdout,"%c  ", rep_carta);
  }
  puts("");

}

/*
 */
void
terminar_juego(){
  imprimir_juego(-1);
  quitar_jugadores(num_jugadores);
  liberar_recursos();
  fprintf(stdout,"%s",fin_juego);
}

/*
  cartas[i] ^= cartas[j];
  cartas[j] ^= cartas[i];
  cartas[i] ^= cartas[j];
*/


//  { puts("");int i;for(i=0; i<CARTAS ;++i) fprintf(stdout, "%d ",cartas[i]);puts("");}
