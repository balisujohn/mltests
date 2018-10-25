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
brain * learn( float (*f)(brain *), params * p/*int inputCount, int outputCount*/)
{
	srand(time(0));
	brain * best =generateSparseBrain(p->mParams);
	float score = 0;
	int sum =0;
	int counter=0;
	int validated = 0;
	while (!validated )
	{	

		brain * candidate = forkBrain(best);


		mutateBrain(candidate,p->mParams);
		brain * testInstance = forkBrain(candidate);



		float newScore = (*f)(testInstance);
		freeBrain(testInstance);
		if (newScore > score)
		{

			FILE *fp;
			fp = fopen("log.txt", "w+");
			printBrainToFile(candidate, fp);
			fclose(fp);

			printf("NEW BEST SCORE: %f\n" , newScore);
			score = newScore;
			freeBrain(best);
			best =candidate;
			//printBrain(best);
			validated = (100 <= score);

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
	analyzeBrain(best,p->mParams->minInputCount,p->mParams->minOutputCount);
	return best;

}



/*
   simple greedy  learning algorithm. 

   GENERATE RANDOM -> MUTATE -> REPLACE ORIGINAL IF MUTATE OFFSPRING SCORES HIGHER

   takes existing brain and problem as in put and trains brain on problem. 


 */


brain * learnFromExistingBrain(brain * b,  float (*f)(brain *), params * p/* int inputCount, int outputCount*/)
{
	srand(time(0));

	brain * best = b;
	brain * benchmarkBrain = forkBrain(best);
	float score = (*f)(benchmarkBrain);
	freeBrain(benchmarkBrain);
	int sum =0;
	int counter=0;
	int validated = (100<=score);
	while (!validated )
	{	

		brain * candidate = forkBrain(best);


		mutateBrain(candidate,p->mParams);
		brain * testInstance = forkBrain(candidate);



		float newScore = (*f)(testInstance);
		freeBrain(testInstance);
		if (newScore > score)
		{

		
			FILE *fp;
			fp = fopen("log.txt", "w+");
			printBrainToFile(candidate, fp);
			fclose(fp);



			printf("NEW BEST SCORE: %f\n" , newScore);
			score = newScore;
			freeBrain(best);
			best =candidate;
			//printBrain(best);
			validated = (100 <= score);

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
	analyzeBrain(best,p->mParams->minInputCount,p->mParams->minOutputCount);
	return best;

}



/*
   simple greedy  learning algorithm. 
   GENERATE RANDOM -> MUTATE -> REPLACE ORIGINAL WITH BEST MUTATION AFTER N MUTATIOBS IF MUTATE OFFSPRING SCORES HIGHER

 */


//deprecated

/*
   brain * multiSucc( float (*f)(brain *), int inputCount, int outputCount, int childCount)
   {
   srand(time(0));

   brain * best = generateBasicBrain();
   float score = 0;
   int sum =0;
   int counter=0;
   int validated = 0;



   brain  ** children = malloc(sizeof(brain * ) * childCount);

   while (!validated)
   {

   for(int i = 0 ; i < childCount; i ++)
   {

   children[i] = forkBrain(best);
   mutateBrain(children[i],inputCount,outputCount);
   }

   float childScore = score;
   brain * bestChild = NULL;	

   for(int i = 0 ; i < childCount; i++ )
   {

   float newChildScore = (*f)(children[i]);
   if (newChildScore >  childScore)
   {
   printf("CHILD ACCEPTED: %f\n", newChildScore);
   childScore = newChildScore;

   if(bestChild != NULL)
   {
   freeBrain(bestChild);
   }			
   bestChild = forkBrain(children[i]);

   }
   freeBrain(children[i]);
   }
   if (childScore > score)
   {

   printf("NEW BEST SCORE: %f\n" , childScore);
   score = childScore;
   freeBrain(best);
   best =forkBrain(bestChild);
//printBrain(best);
validated = (100 <= score);

}
if(bestChild != NULL)
{
freeBrain(bestChild);
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

free(children);
FILE *fp;
fp = fopen("log.txt", "w+");
printBrainToFile(best, fp);
fclose(fp);
printBrain(best);
analyzeBrain(best, inputCount, outputCount);
//	freeBrain(best);
return best;
}
//deprecated
brain * populationLearn( float (*f)(brain *), int inputCount, int outputCount, int populationCount, int generations)
{
	srand(time(0));


	float bestScore[populationCount];
	float avgScore[populationCount];
	float stddev[populationCount];

	float improvementLikelyhoodHeuristic[populationCount];


	brain * bestPopulationBrain = NULL;
	float bestPopulationScore = 0;



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



			float newScore = (*f)(testInstance);
			freeBrain(testInstance);
			if (newScore > bestScore[i])
			{

				printf("NEW BEST SCORE: %f\n" , newScore);
				bestScore[i] = newScore;


				freeBrain(population[brainIndex]);

				population[brainIndex] =candidate;
				if (bestScore[i] > bestPopulationScore)
				{
					bestPopulationScore = bestScore[i];
					if(bestPopulationBrain!=NULL)
					{					
						freeBrain(bestPopulationBrain);
					}
					bestPopulationBrain = forkBrain(population[brainIndex]);
					if(newScore >= 100)
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
	free(population);



	FILE *fp;
	fp = fopen("log.txt", "w+");
	printBrainToFile(bestPopulationBrain, fp);
	fclose(fp);
	printBrain(bestPopulationBrain);
	analyzeBrain(bestPopulationBrain,inputCount,outputCount);
	//freeBrain(bestPopulationBrain);
	return bestPopulationBrain;

}
*/

