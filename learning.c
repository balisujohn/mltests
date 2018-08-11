#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include"brain.h"
#include"analysis.h"
#include"learning.h"



//John Balis 2018
//for support email balisujohn@gmail.com 



/*
   simple greedy  learning algorithm. 

   GENERATE RANDOM -> MUTATE -> REPLACE ORIGINAL IF MUTATE OFFSPRING SCORES HIGHER




 */
void learn( int (*f)(brain *), int inputCount, int outputCount)
{
	srand(time(0));

	brain * best =generateBasicBrain();
	int rigor = 10000;
	int score = 0;
	int sum =0;
	int counter=0;
	int validated = 0;
	while (!validated )
	{	

		brain * candidate = forkBrain(best);


		mutateBrain(candidate,inputCount,outputCount);
		brain * testInstance = forkBrain(candidate);



		int newScore = (*f)(testInstance);
		freeBrain(testInstance);
		if (newScore > score)
		{

			printf("NEW BEST SCORE: %d\n" , newScore);
			score = newScore;
			freeBrain(best);
			best =candidate;
			//printBrain(best);
			validated = (100 == score);

		}
		else
		{
			freeBrain(candidate);


		}
		sum += newScore;
		counter++;
		if (counter == 100)
		{
			printf("LAST 100 AVERAGE: %f\n", sum/100.0);


			sum = 0;
			counter = 0;
		}
	}


	FILE *fp;
	fp = fopen("log.txt", "w+");
	printBrainToFile(best, fp);
	fclose(fp);
	printBrain(best);
	//analyzeBrain(best,inputCount,outputCount);
	freeBrain(best);

}


/*
   simple greedy  learning algorithm. 
   GENERATE RANDOM -> MUTATE -> REPLACE ORIGINAL WITH BEST MUTATION AFTER N MUTATIOBS IF MUTATE OFFSPRING SCORES HIGHER

 */



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
			mutateBrain(children[i],inputCount,outputCount);
		}

		int childScore = score;
		brain * bestChild;	

		for(int i = 0 ; i < 500; i++ )
		{
			brain * candidate = forkBrain(best);
			mutateBrain(candidate,inputCount,outputCount);

			int newChildScore = (*f)(candidate);
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
	printBrain(best);

	//analyzeBrain(best, inputCount, outputCount);

}

void populationLearn( int (*f)(brain *), int inputCount, int outputCount, int populationCount, int generations)
{
	srand(time(0));


	int bestScore[populationCount];
	int avgScore[populationCount];
	int stddev[populationCount];

	int improvementLikelyhoodHeuristic[populationCount];


	brain * bestPopulationBrain = NULL;
	int bestPopulationScore = 0;



	brain ** population;
	assert(population =  malloc(sizeof(brain *) * populationCount));
	for (int i = 0 ; i < populationCount; i++)
	{
		bestScore[i] = 0;
		population[i] = generateBasicBrain();	
	}



	int brainIndex = 0;
	while(bestPopulationScore < 100)
	{
		int sum = 0;
		int counter = 0;

		for(int i = 0 ; i < generations; i ++)
		{

			brain * candidate = forkBrain(population[brainIndex]);


			mutateBrain(candidate,inputCount,outputCount);
			brain * testInstance = forkBrain(candidate);



			int newScore = (*f)(testInstance);
			freeBrain(testInstance);
			if (newScore > bestScore[i])
			{

				printf("NEW BEST SCORE: %d\n" , newScore);
				bestScore[i] = newScore;


				freeBrain(population[brainIndex]);

				population[brainIndex] =candidate;
				if (bestScore[i] > bestPopulationScore)
				{
					bestPopulationScore = bestScore[i];
					if(bestPopulationBrain)
					{					
						freeBrain(bestPopulationBrain);
					}
					bestPopulationBrain = forkBrain(population[brainIndex]);
					if(newScore == 100)
					{
						break;

					}
				}

			}
			else
			{
				freeBrain(candidate);


			}
			sum += newScore;
			counter++;
			if (counter == generations)





			{
				printf("LAST %d AVERAGE: %f\n", generations ,sum/(float)generations);


				sum = 0;
				counter = 0;
			}



		}	




		brainIndex++;
		if (brainIndex == populationCount)
		{
			brainIndex = 0;
		}
	}

	for (int i = 0 ; i < populationCount; i++)
	{
		freeBrain(population[i]);	
	}




	FILE *fp;
	fp = fopen("log.txt", "w+");
	printBrainToFile(bestPopulationBrain, fp);
	fclose(fp);
	printBrain(bestPopulationBrain);
	//analyzeBrain(bestPopulationBrain,inputCount,outputCount);
	freeBrain(bestPopulationBrain);

}


