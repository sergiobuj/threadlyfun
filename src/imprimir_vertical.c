/* @(#)imprimir_vertical.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char * argv[])
{
  

  int cartas[] = { 10, 1 ,4 ,3, 4, 4, 10, 4 ,10,} , i;
  char win[52]="", lose[52]="";
  int count_w=0, count_l=0 , max_l=0; 
  for(i = 0; i < 9; ++i){
    if( cartas[i] == 0){
      ++count_w;
    }else if( cartas[i] == max_l ){
      ++count_l;
    }else if( max_l < cartas[i] ){
      max_l = cartas[i];
      count_l = 1;
    }
  }
  for(i = 0; i < 9; ++i){
    if( cartas[i] == 0  ){
      sprintf(win,"%s %d",win, i + 1 );
    }else if(cartas [i] == max_l){
      sprintf(lose,"%s %d",lose, i + 1 );
    }
  }
  printf( "cwin %d clos %d maxl %d  \n",count_w,count_l,max_l );
  puts(win);
  puts(lose);


  return 0;
}
