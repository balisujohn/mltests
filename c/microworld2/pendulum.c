#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<string.h>

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
float angle =((randFloat() *M_PI)/2.0) +( M_PI/4.0);
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
float baseXVel = w->baseXVel + baseXAccel;
float baseXPos = w->baseXPos + baseXVel;

if(baseXPos > 2)
{
 baseXAccel = 0;
 baseXPos = 2;
 baseXVel = 0;
}

if(baseXPos < -2) 
{
baseXAccel = 0;
baseXPos = -2;
baseXVel = 0;	


}
float baseYPos = 0;

float weightXAccel = (GRAVITY * cos(angle)) + (sin(angle) * baseXAccel);
float weightYAccel = (GRAVITY * sin(angle)) + ( cos(angle) * baseXAccel);
//printf("WEIGHT GRAV Y ACCEL: %f, WEIGHT BASE Y ACCEL: %f\n", (GRAVITY * sin(angle)),   ( cos(angle) * baseXAccel * 5000000));



float weightXVel = w->weightXVel + weightXAccel;
float weightYVel = w->weightYVel + weightYAccel;
if (weightYVel > 1) weightYVel = 1;
if (weightYVel < -1) weightYVel = -1;
float weightXPos = w->weightXPos +  weightXVel * .1;
float weightYPos = w->weightYPos +  weightYVel * .1;
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
		printf("|");
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
	
		printf("|\n");
	}
}




float evaluateMicroWorldPerformance(brain * b)
{
	

	const int trials = 100;
	const int survivalTime = 100;	


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
		int normedWeightYVel = abs((int)(63 * world->weightYVel));
		if (normedWeightYVel > 255) 
		{
		normedWeightYVel = 255;
		}
		int normedHeight = (int)(world->weightYPos/PENDULUM_LENGTH)* 15;
		if(normedHeight > 15)
		{
			normedHeight = 15;
		} 
		mapIntToUnaryArray(normedWeightXVel,&(inputs[1]) ,8);
		mapIntToUnaryArray(normedWeightYVel,&(inputs[10]) ,8);		
		mapIntToUnaryArray(normedHeight,&(inputs[18]) ,4);
		
		for(int c = 0; c< 5; c++)
		{	
		advanceBrain(testInstance,&(inputs[0]),22,&(outputs[0]),9);
		}

	 	int brainOutput = mapArrayToInt(&(outputs[0]), 8);
		if(outputs[8])
		{
		brainOutput *= -1;
		}
		//if(brainOutput) printf("%i\n",brainOutput);
		advancePendulumWorld(world,brainOutput/255.0);
		}
		free(world);
		freeBrain(testInstance);
		
	}	
	return (((float)score /(trials * survivalTime)) * 100)/.95;
}

void m2Analysis(brain * b)
{
while(1)
{
        int score = 0;
	pendulumWorld * world = initRandomPendulumWorld();
		brain * testInstance = forkBrain(b);
		while ( world->weightYPos > 0)
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
		int normedWeightYVel = abs((int)(63 * world->weightYVel));
		if (normedWeightYVel > 255) 
		{
		normedWeightYVel = 255;
		}
		int normedHeight = (int)((world->weightYPos/PENDULUM_LENGTH)* 15);
		if(normedHeight > 15)
		{
			normedHeight = 15;
		} 
		mapIntToUnaryArray(normedWeightXVel,&(inputs[1]) ,8);
		mapIntToUnaryArray(normedWeightYVel,&(inputs[10]) ,8);		
		mapIntToUnaryArray(normedHeight,&(inputs[18]) ,4);
		
		for(int c = 0; c< 5; c++)
		{	
		advanceBrain(testInstance,&(inputs[0]),22,&(outputs[0]),9);
		}
  struct timespec interval;
                interval.tv_sec = 0;
                interval.tv_nsec = 200000000;
                nanosleep(&interval, NULL);
                graphicalDisplay(world);
		printf("X VELOCITY: %i, Y VELOCITY: %i, HEIGHT: %i\n", normedWeightXVel, normedWeightYVel, normedHeight);


		int brainOutput = mapArrayToInt(&(outputs[0]), 8);
		if(outputs[8])
		{
			brainOutput *= -1;
		}
		//if(brainOutput) printf("%i\n",brainOutput);
		advancePendulumWorld(world,brainOutput/255.0);
		}
		free(world);
		freeBrain(testInstance);



		printf("\033[2J");
		printf("SCORE: %i\n", score);
		struct timespec interval;
		interval.tv_sec = 1;
		interval.tv_nsec = 0;   
		nanosleep(&interval, NULL);



}

}



int main(int argc, char * argv[])
{
	srand(time(0));


	/*
	   int array[8];
	   int value = 254;
	   mapIntToArray(value, &(array[0]), 8);
	   int result = mapArrayToInt(&(array[0]),8);
	   assert(value == result);


	   return 1 ;
	 */

	params * p = initializeDefaultParams();
	p->mParams->initialNeuronCount = 32;
	p->mParams->potentialProb = .3;	


	if(argc == 2 && strstr(argv[1], "train"))
	{
		brain * resultBrain = learn(evaluateMicroWorldPerformance, p);
	}
	else if(argc == 3 && strstr(argv[1],"analyze"))
	{
		srand(time(0));
		FILE * fp = fopen(argv[2], "r");
		brain * b = loadBrainFromFile(fp);
		m2Analysis(b);
	}
	else if (argc == 3 && strstr(argv[1], "improve"))
	{
		FILE * brainFile = fopen(argv[2], "r");
		brain * starter = loadBrainFromFile(brainFile);
		brain * resultBrain = learnFromExistingBrain(starter, evaluateMicroWorldPerformance, p); 
	}
	else
	{
		printf("INVALID USAGE\n");
	}


	return 1;	

}



