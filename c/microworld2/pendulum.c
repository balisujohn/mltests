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
w->baseYPos = .001;
w->baseXPos = .001;
w->baseXVel = 0;
w->baseXAccel = 0;
float angle = randFloat() *M_PI;
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



float baseXPos = w->baseXPos;
float baseYPos = w->baseYPos;
float weightXAccel = GRAVITY * cos(angle);
float weightYAccel = GRAVITY * sin(angle);
float weightXVel = w->weightXVel + w->weightXAccel;
float weightYVel = w->weightYVel + w->weightYAccel;
float weightXPos = w->weightXPos +  w->weightXVel * .1;
float weightYPos = w->weightYPos +  w->weightYVel * .1;

float weightToBaseX = weightXPos - w->baseXPos; 
float weightToBaseY = weightYPos - baseYPos;

float norm = sqrt(pow(weightToBaseX,2) + pow(weightToBaseY, 2));

weightXPos = baseXPos + ((weightToBaseX / norm)* PENDULUM_LENGTH);
weightYPos = baseYPos + ((weightToBaseY / norm) * PENDULUM_LENGTH);

w->weightXAccel = weightXAccel;
w->weightYAccel = weightYAccel;
w->weightXVel = weightXVel;
w->weightYVel = weightYVel;
w->weightXPos = weightXPos;
w->weightYPos  = weightYPos;




}

void displayPendulum(pendulumWorld * w)
{
printf("WEIGHT COORDINATES ARE: %f, %f\n", w->weightXPos, w->weightYPos);
}
void graphicalDisplay(pendulumWorld * w)
{
	printf("\033[2J");
	for(int c = 19; c >= 0; c --)
	{
		for(int i = 19; i >= 0; i--)
		{
		if(w->weightXPos >= -2.0 + (i*(.2)) && w->weightXPos <= -2.0 + ((i+1) * .2 ) && (w->weightYPos >= -2.0 + (c*(.2)) && w->weightYPos <= -2.0 + ((c+1) * .2 )))
		{
		printf("X ");
		}
		else if(w->baseXPos >= -2.0 + (i*(.2)) && w->baseXPos <= -2.0 + ((i+1) * .2 ) && ((w->baseYPos >= -2.0 + (c*(.2))) && ( w->baseYPos <= -2.0 + ((c+1) * .2 ))))
		{
		printf("Y ");
		}
		else
		{
		printf("  ");
		}

		}
	printf("\n");
	}
}





int main(int argc, char * argv[])
{

	srand(time(0));

	pendulumWorld * test = initRandomPendulumWorld(); 

	while(test->weightYPos > 0)
	{
		struct timespec interval;
		interval.tv_sec = 0;
		interval.tv_nsec = 50000000;
		nanosleep(&interval, NULL);
		graphicalDisplay(test);
		advancePendulumWorld(test);
	}


	return 1;
}



