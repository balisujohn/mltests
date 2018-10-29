#ifndef PENDULUM_H
#define PENDULUM_H

 

#define PENDULUM_LENGTH 1
#define GRAVITY -.5
#define RIGHT_X_BOUND 1
#define LEFT_X_BOUND -1


#define FAILED_WALL_COLLISION
#define ACTIVE

//John Balis 2018
//for support email balisujohn@gmail.com

struct pendulumWorld{
int time;
int failed;

float weightXPos;
float weightYPos;
float weightXVel;
float weightYVel;
float weightXAccel;
float weightYAccel;

float baseYPos;
float baseXPos;
float baseXVel;
float baseXAccel;

} typedef pendulumWorld;


#endif
