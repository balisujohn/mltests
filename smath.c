#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"brain.h"
#include"utils.h"




int evaluateAdditionPerformance(brain * b , int rigor)
{
	int score = 0;

	//	for(int i = 0; i < rigor; i ++)	
	//	{
	for(int x1 = 0; x1 < 8; x1++)	
	{
		for(int x2 = 0; x2 < 8; x2++)	
		{	
			brain * testInstance = forkBrain(b);

			//		printf("checkpoint2\n");
			//	int x1 = randRange(8);
			//	int x2 = randRange(8);
			int expectedResult = (x1 + x2);
			//			printf("X0: %d X2: %d EXPECTED: %d\n", x1, x2, expectedResult);
			int result[] = {0,0,0,0};
			for(int c = 0; c < 20; c++)
			{
				int inputs[] = {  x1 & 1, (x1>>1) &1, (x1>>2)&1, x2 & 1,( x2>>1)  &1, (x2>>2)&1};
				/*result =*/ advanceBrain(testInstance, inputs,6, result, 4);
				//	printBrain(testInstance);
				//printBrain(testInstance);

			}
			freeBrain(testInstance);

			if (!((result[0] ^ (expectedResult >>3)) & 1 ))score++;
			if (!((result[1] ^ (expectedResult >>2)) & 1 ))score++;
			if (!((result[2] ^ (expectedResult >>1)) & 1 ))score++;
			if (!( (coinFlip() ^  expectedResult) & 1 ))score++;
		}
	}

	//	}

	return score;

}
/*
   void teste()
   {
   brain * b = generateBasicBrain(); 
   int sum = 0;
   for (int i = 0 ; i < 10000; +)



   }
 */

void baseLineTest()
{
	brain * baseLine = generateXorBrain();
	brain * testInstance = forkBrain(baseLine);
	printf("SCORE: %d\n",evaluateAdditionPerformance(testInstance, 100));



}



int multiSucc(int population)
{
	//baseLineTest();
	//exit(0);



	printf("checkpoint0\n");
	srand(time(0));

	brain * best =generateBasicBrain();//generateXorBrain();
	int rigor = 1000;
	int score = 0;
	int sum =0;
	int counter=0;
	int validated = 0;



	brain  ** children = malloc(sizeof(brain * ) * population);

	while (!validated)
	{
		//		printf("checkpoint1\n");

		for(int i = 0 ; i < population; i ++)
		{

			children[i] = forkBrain(best);
			mutateBrain(children[i]);
		}

		int childScore = 0;
		brain * bestChild;	

		for(int i = 0 ; i < population; i++ )
		{
			brain * candidate = forkBrain(best);

			//		printf("checkpoint1.5\n");

			mutateBrain(candidate);




			//brain * testInstance = forkBrain(candidate);
			//		printf("checkpoint1.75\n");

			//		int newScore = evaluateXorPerformance(testInstance, rigor);
			//			printf("NEW SCORE: %d\n" , newScore);


			int newChildScore = evaluateAdditionPerformance(candidate,rigor);
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
			validated = (64 == score);

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


	return 0;
}

int main (int argc, char * argv[])
{
	//	baseLineTest();
	//	exit(0);

	//	multiSucc(500);
	//	exit(0);

	printf("checkpoint0\n");
	srand(time(0));

	brain * best =generateBasicBrain();//generateXorBrain();
	int rigor = 100;
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


		int newScore = evaluateAdditionPerformance(testInstance,rigor);

		if (newScore > score)
		{

			printf("NEW BEST SCORE: %d\n" , newScore);
			score = newScore;
			freeBrain(best);
			best =candidate;
			//printBrain(best);
			validated = (rigor == score);

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


	return 0;
}
