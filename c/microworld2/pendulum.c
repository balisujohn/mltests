#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include"pendulum.h"
#include"../utils.h"



//John Balis 2018
//for support email balisujohn@gmail.com 


//function to allocate a pendulum world and initialize it to a random starting state


pendulumWorld * initRandomPendulumWorld()
{
pendulumWorld w = malloc(sizeof(pendulumWorld));
w->baseXPos = (randFloat()*2)-1; // sets the base x position of our pendulum randomly
w->baseYVel = 0;
w->baseYAccel = GRAVITY;
float angle = randFloat() * PI;
w->weightXPos = cos(angle) * PENDULUM_LENGTH;
w->weightYPos = sin(angle) * PENDULUM_LENGTH;
w->weightXVel = 0;
w->weightYVel = 0;
w->weightXAccel = 0;
return w;
}

int advancePendulumWorld(pendulumWorld * w)
{
float angle = asin(w->weightYPos/abs(w->weightXPos - w->baseXPos));
newBaseXVel = w->baseWeightXVel + cos(angle) * w->baseWeightAccel;
newWeightXVel = w->weightXVel  
}





}
