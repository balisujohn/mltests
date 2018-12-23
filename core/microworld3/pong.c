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

pongWorld * generatePongWorld(){





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
	p->mParams->initialNeuronCount = 34;
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



