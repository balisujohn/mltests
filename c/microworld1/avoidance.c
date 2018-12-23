#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include"world.h"
#include"m1analysis.h"
#include"../brains/brain.h"
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


int main(int argc, char * argv[])
{
/*	save-load test protocol hopefully will never be needed again
	FILE * fp = fopen("save.1","r");
	brain * b = loadBrainFromFile(fp);
	printBrain(b);
	fclose(fp);
	FILE * fp2 = fopen("log.txt", "w+");
	printBrainToFile(b,fp2);
	exit(0);
	
*/

	params * p = initializeDefaultParams();
	p->mParams->initialNeuronCount = 11;



	if(argc == 2 && strstr(argv[1], "train"))
	{
		brain * resultBrain = learn(evaluateMicroWorldPerformance, p);
	}
	else if(argc == 3 && strstr(argv[1],"analyze"))
	{
		srand(time(0));
		FILE * fp = fopen(argv[2], "r");
		brain * b = loadBrainFromFile(fp);
		analyzeBrainMicroWorld1(b);
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


/*

	if (argc == 2)
	{
	if(strcmp(argv[1], "train"))
	{
	srand(time(0));
	//populationLearn(evaluateMicroWorldPerformance, 4,3,10,10);

	params * p = initializeDefaultParams();
	p->mParams->initialNeuronCount = 11;

        brain * resultBrain = learn(evaluateMicroWorldPerformance, p);
	analyzeBrainMicroWorld1(resultBrain);
	}
	}*/
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
