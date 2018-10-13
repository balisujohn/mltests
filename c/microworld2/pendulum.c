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
pendulumWorld * w = malloc(sizeof(pendulumWorld));
w->baseXPos = (randFloat()*2)-1; // sets the base x position of our pendulum randomly
w->baseXVel = 0;
w->baseXAccel = 0;
float angle = randFloat() * PI;
w->weightXPos = cos(angle) * PENDULUM_LENGTH;
w->weightYPos = sin(angle) * PENDULUM_LENGTH;
w->weightXVel = 0;
w->weightYVel = 0;
w->weightXAccel = 0;
w->weightYAccel = 0;
return w;
}

int advancePendulumWorld(pendulumWorld * w)
{
float angle = atan(w->weightYPos/abs(w->weightXPos - w->baseXPos));
w->weightXAccel = cos(angle);
w->weightYAccel = sin(angle);
w->weightXVel += w->weightXAccel;
w->weightYVel += w->weightYAccel;
w->weightXPos += w->weightYVel * .001;
w->weightYPos += w->weightYVel * .001;  
}

void displayPendulum(pendulumWorld * w)
{
printf("WEIGHT COORDINATES ARE: %f, %f\n", w->weightXPos, w->weightYPos);
}


int main(int argc, char * argv[])
{

srand(55);

pendulumWorld * test = initRandomPendulumWorld(); 

for(int i = 0; i < 100; i++)
{
displayPendulum(test);
advancePendulumWorld(test);
}
return 1;
}



