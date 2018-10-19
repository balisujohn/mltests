#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<time.h>
#include<math.h>

#include"../brain.h"

#include"pendulum.h"

#include"../learning.h"
#include"../utils.h"



//John Balis 2018
//for support email balisujohn@gmail.com 


//function to allocate a pendulum world and initialize it to a random starting state


pendulumWorld * initRandomPendulumWorld()
{
pendulumWorld * w = malloc(sizeof(pendulumWorld));
w->time = 0;
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

int advancePendulumWorld(pendulumWorld * w, float baseAccel)
{
w->time += 1;
float angle = atan(w->weightYPos/abs(w->weightXPos - w->baseXPos));



float baseXAccel = baseAccel;
float baseXVel = w->baseXVel + w->baseXAccel;
float baseXPos = w->baseXPos + w->baseXVel * .1;
float baseYPos = 0;

float weightXAccel = GRAVITY * cos(angle) + sin(angle) * baseXAccel;
float weightYAccel = GRAVITY * sin(angle) + cos(angle) * baseXAccel;

float weightXVel = w->weightXVel + w->weightXAccel;
float weightYVel = w->weightYVel + w->weightYAccel;
float weightXPos = w->weightXPos +  w->weightXVel * .1;
float weightYPos = w->weightYPos +  w->weightYVel * .1;
float weightToBaseX = weightXPos - baseXPos; 
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
w->baseXAccel = baseXAccel;
w->baseXVel = baseXVel;
w->baseXPos = baseXPos;



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




float evaluateMicroWorldPerformance(brain * b)
{
	

	const int trials = 100;
	const int survivalTime = 1000;	


	int score = 0;
	for(int i = 0; i < trials; i ++)
	{

		pendulumWorld * world = initRandomPendulumWorld();
		brain * testInstance = forkBrain(b);
		while (world->time < survivalTime && world->weightYPos > 0)
		{
		score+=1;
		
		
		int inputs[22];
		int outputs[9];
		inputs[0] = world->weightXVel > 0;
		inputs[9] = world->weightYVel > 0;
		int normedWeightXVel = abs((int)(255* world->weightXVel));
		if (normedWeightXVel > 255) 
		{
		normedWeightXVel = 255;
		} 
		int normedWeightYVel = abs((int)(255* world->weightYVel));
		if (normedWeightYVel > 255) 
		{
		normedWeightYVel = 255;
		}
		int normedHeight = (int)(world->weightYPos/PENDULUM_LENGTH)* 15;
		if(normedHeight > 15)
		{
			normedHeight = 15;
		} 
		mapIntToArray(normedWeightXVel,&(inputs[1]) ,8);
		mapIntToArray(normedWeightYVel,&(inputs[10]) ,8);		
		mapIntToArray(normedHeight,&(inputs[18]) ,4);
		
			
		advanceBrain(testInstance,&(inputs[0]),22,&(outputs[0]),9);

	 	int brainOutput = mapArrayToInt(&(outputs[0]), 8);
		if(outputs[8])
		{
		brainOutput *= -1;
		}
		//if(brainOutput) printf("%i\n",brainOutput);
		advancePendulumWorld(world,brainOutput*2);
		}
		free(world);
		freeBrain(testInstance);
		
	}	
	return (((float)score /(trials * survivalTime)) * 100)/.95;
}



int main(int argc, char * argv[])
{


	/*
	int array[8];
	int value = 254;
	mapIntToArray(value, &(array[0]), 8);
	int result = mapArrayToInt(&(array[0]),8);
	assert(value == result);


	return 1 ;
	*/

	srand(time(0));

	params * p = initializeDefaultParams();
	p->mParams->initialNeuronCount = 32;
	p->mParams->potentialProb = .3;	
        brain * resultBrain = learn(evaluateMicroWorldPerformance, p);
	

	return 1;	

	pendulumWorld * test = initRandomPendulumWorld(); 



	while(test->weightYPos > 0)
	{
		struct timespec interval;
		interval.tv_sec = 0;
		interval.tv_nsec = 50000000;
		nanosleep(&interval, NULL);
		graphicalDisplay(test);
		advancePendulumWorld(test,((randFloat()*2) -1)/10);
	}


	return 1;
}



