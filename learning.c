#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include"brain.h"
#include"analysis.h"
#include"learning.h"


//general learning function
void learn( int (*f)(brain *), int inputCount, int outputCount)
{
	srand(time(0));

	brain * best =generateBasicBrain();//generateXorBrain();
	int rigor = 10000;
	int score = 0;
	int sum =0;
	int counter=0;
	int validated = 0;
	while (!validated)
	{
		//		printf("checkpoint1\n");
		brain * candidate = forkBrain(best);

		//		printf("checkpoint1.5\n");

		mutateBrain(candidate);
		brain * testInstance = forkBrain(candidate);
		//		printf("checkpoint1.75\n");

		//		int newScore = evaluateXorPerformance(testInstance, rigor);
		//			printf("NEW SCORE: %d\n" , newScore);


		int newScore = (*f)(testInstance);//evaluateOrPerformance(testInstance,rigor);

		if (newScore > score)
		{

			printf("NEW BEST SCORE: %d\n" , newScore);
			score = newScore;
			freeBrain(best);
			best =candidate;
			//printBrain(best);
			validated = (100 == score);

		}
		sum += newScore;
		counter++;
		if (counter == 100)
		{
			//printf("LAST 100 AVERAGE: %f\n", sum/100.0);


			sum = 0;
			counter = 0;
		}
	}


	FILE *fp;
	fp = fopen("log.txt", "w+");
	printBrainToFile(best, fp);
	fclose(fp);
	printBrain(best);
	analyzeBrain(best,2,1);

}

void multiSucc( int (*f)(brain *), int inputCount, int outputCount)
{
	srand(time(0));

	brain * best =generateBasicBrain();
	int rigor = 10000;
	int score = 0;
	int sum =0;
	int counter=0;
	int validated = 0;



	brain  ** children = malloc(sizeof(brain * ) * 500);

	while (!validated)
	{

		for(int i = 0 ; i < 500; i ++)
		{

			children[i] = forkBrain(best);
			mutateBrain(children[i]);
		}

		int childScore = score;
		brain * bestChild;	

		for(int i = 0 ; i < 500; i++ )
		{
			brain * candidate = forkBrain(best);
			mutateBrain(candidate);

			int newChildScore = (*f)(candidate);//evaluateXorPerformance(candidate,rigor);
			if (newChildScore >  childScore)
			{
				printf("CHILD ACCEPTED: %d\n", newChildScore);
				childScore = newChildScore;
				bestChild = candidate;

			}
		}
		if (childScore > score)
		{

			printf("NEW BEST SCORE: %d\n" , childScore);
			score = childScore;
			freeBrain(best);
			best =bestChild;
			//printBrain(best);
			validated = (100 == score);

		}
		sum += childScore;
		counter++;
		if (counter == 100)
		{
			//printf("LAST 100 AVERAGE: %f\n", sum/100.0);


			sum = 0;
			counter = 0;
		}
	}


	FILE *fp;
	fp = fopen("log.txt", "w+");
	printBrainToFile(best, fp);
	fclose(fp);


	analyzeBrain(best, 2, 1);

}


