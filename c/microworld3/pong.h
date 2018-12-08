#ifndef PONG_H
#define PONG_H

#define PONG_BOARD_SIZE 20
#define PADDLE_LENGTH 3

 
//John Balis 2018
//for support email balisujohn@gmail.com

struct pongWorld{
char [PONG_BOARD_SIZE][PONG_BOARD_SIZE];
int p1YPos;
int p2YPos;
int p1Score;
int p2Score;
} typedef pongWorld;



#endif
