#ifndef PENDULUM_H
#define PENDULUM_H

 

#define PENDULUM_LENGTH 1
#define GRAVITY -0.1
#define RIGHT_X_BOUND 1
#define LEFT_X_BOUND -1


//John Balis 2018
//for support email balisujohn@gmail.com

struct pendulumWorld{


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
