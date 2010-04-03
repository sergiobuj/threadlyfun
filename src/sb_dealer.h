/* @(#)sb_dealer.h
 */

#ifndef _DEALER_H
#define _DEALER_H 1

#define BARAJAS 1
#define CARTAS 52*BARAJAS
#define SWAP(a,b)({(a)^=(b);(b)^=(a);(a)^=(b);})


int cartas[ CARTAS ];
int game_over;


#endif /* _DEALER_H */