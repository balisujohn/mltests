#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"world.h"
#include"m1analysis.h"
#include"../brain.h"
#include"../learning.h"
//John Balis 2018
//for support email balisujohn@gmail.com 



float evaluateMicroWorldPerformance(brain * b)
{
	const int trials = 100;
	const int survivalTime = 1000;	


	int score = 0;
	for(int i = 0; i < trials; i ++)
	{
		world * w = generateWorld();
		initializeBasicWorld(w);
		brain * testInstance = forkBrain(b);
		while(w->age < survivalTime && !(w->dead))	
		{
			//printWorldPop(w);
			advanceWorldState(w,b);

		}
		score += w->age;
		freeWorld(w);
		freeBrain(testInstance);
	}	
	return (((float)score /(trials * survivalTime)) * 100)/.95;
}


int main(int arc, char * argv[])
{

	srand(time(0));
	//populationLearn(evaluateMicroWorldPerformance, 4,3,10,10);
        brain * resultBrain = learn(evaluateMicroWorldPerformance, 4,3);
	analyzeBrainMicroWorld1(resultBrain);
	
	/*



	   world * w = generateWorld();
	   brain * b = generateBasicBrain();
	   printWorldPop(w);
	   initializeBasicWorld(w);
	   printWorldPop(w);
	   advanceWorldState(w,b);
	   printWorldPop(w);

	   advanceWorldState(w,b);
	   printWorldPop(w);
	   advanceWorldState(w,b);
	   printWorldPop(w);
	   advanceWorldState(w,b);
	   printWorldPop(w);
	   advanceWorldState(w,b);
	   printWorldPop(w);

	 */		exit(0);
}
