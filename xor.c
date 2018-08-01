#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"brain.h"
#include"utils.h"



/*
int evaluateXorPerformance(brain * b , int rigor)
{
	int score = 0;

	for(int i = 0; i < rigor; i ++)	
	{
		brain * testInstance = forkBrain(b);

		//		printf("checkpoint2\n");
		int x1 = coinFlip();
		int x2 = coinFlip();
		int expectedResult = (x1 ^ x2);
					printf("X0: %d X2: %d EXPECTED: %d\n", x1, x2, expectedResult);
		int result = 0;
		for(int c = 0; c < 3; c++)
		{
			int inputs[] = {x1*(c==0),x2*(c==0) };
			/result =/ advanceBrain(testInstance, inputs,2, &result, 1);
			//	printBrain(testInstance);
			//printBrain(testInstance);

		}
		freeBrain(testInstance);
		if (result == expectedResult)score++;
		printf("RESULT: %d EXPECTED RESULT: %d\n", result, expectedResult);
	}

	return score;

}*/

int evaluateAndPerformance(brain * b , int rigor)
{
	int score = 0;


	brain * testInstance = forkBrain(b);
	brain * testInstance2 = forkBrain(b);
	brain * testInstance3 = forkBrain(b);
	brain * testInstance4 = forkBrain(b);

	int result = 0;
	int result2   = 0;
	int result3 = 0;
	int result4  = 0;

	int inputs[] = { 1,0 };
	int inputs2[] = { 0,0 };
	int inputs3[] = { 1,1 };
	int inputs4[] = { 0,1 };


	int expectedResult = 0;
	int expectedResult2 = 0;
	int expectedResult3 = 1;
	int expectedResult4 = 0;


	for(int c = 0; c < 3; c++)
	{
		advanceBrain(testInstance, inputs,2, &result, 1);
		advanceBrain(testInstance2, inputs2,2, &result2, 1);
		advanceBrain(testInstance3, inputs3,2, &result3, 1);
		advanceBrain(testInstance4, inputs4,2, &result4, 1);



		//	printBrain(testInstance);
		//printBrain(testInstance);

	}
	freeBrain(testInstance);
	freeBrain(testInstance2);
	freeBrain(testInstance3);
	freeBrain(testInstance4);




	if (result==expectedResult)score++;
	if (result2==expectedResult2)score++;
	if (result3==expectedResult3)score++;
	if (result4==expectedResult4)score++;



	return score;

}


int evaluateOrPerformance(brain * b , int rigor)
{
	int score = 0;


	brain * testInstance = forkBrain(b);
	brain * testInstance2 = forkBrain(b);
	brain * testInstance3 = forkBrain(b);
	brain * testInstance4 = forkBrain(b);

	int result = 0;
	int result2   = 0;
	int result3 = 0;
	int result4  = 0;

	int inputs[] = { 1,0 };
	int inputs2[] = { 0,0 };
	int inputs3[] = { 1,1 };
	int inputs4[] = { 0,1 };


	int expectedResult = 1;
	int expectedResult2 = 0;
	int expectedResult3 = 1;
	int expectedResult4 = 1;


	for(int c = 0; c < 3; c++)
	{
		advanceBrain(testInstance, inputs,2, &result, 1);
		advanceBrain(testInstance2, inputs2,2, &result2, 1);
		advanceBrain(testInstance3, inputs3,2, &result3, 1);
		advanceBrain(testInstance4, inputs4,2, &result4, 1);



		//	printBrain(testInstance);
		//printBrain(testInstance);

	}
	freeBrain(testInstance);
	freeBrain(testInstance2);
	freeBrain(testInstance3);
	freeBrain(testInstance4);




	if (result==expectedResult)score++;
	if (result2==expectedResult2)score++;
	if (result3==expectedResult3)score++;
	if (result4==expectedResult4)score++;



	return score;

}


int evaluateXorPerformance(brain * b , int rigor)
{
	int score = 0;


	brain * testInstance = forkBrain(b);
	brain * testInstance2 = forkBrain(b);
	brain * testInstance3 = forkBrain(b);
	brain * testInstance4 = forkBrain(b);

	int result = 0;
	int result2   = 0;
	int result3 = 0;
	int result4  = 0;

	int inputs[] = { 1,0 };
	int inputs2[] = { 0,0 };
	int inputs3[] = { 1,1 };
	int inputs4[] = { 0,1 };


	int expectedResult = 1;
	int expectedResult2 = 0;
	int expectedResult3 = 0;
	int expectedResult4 = 1;


	for(int c = 0; c < 3; c++)
	{
		advanceBrain(testInstance, inputs,2, &result, 1);
		advanceBrain(testInstance2, inputs2,2, &result2, 1);
		advanceBrain(testInstance3, inputs3,2, &result3, 1);
		advanceBrain(testInstance4, inputs4,2, &result4, 1);



		//	printBrain(testInstance);
		//printBrain(testInstance);

	}
	freeBrain(testInstance);
	freeBrain(testInstance2);
	freeBrain(testInstance3);
	freeBrain(testInstance4);




	if (result==expectedResult)score++;
	if (result2==expectedResult2)score++;
	if (result3==expectedResult3)score++;
	if (result4==expectedResult4)score++;



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
	printf("SCORE: %d\n",evaluateXorPerformance(testInstance, 100));



}



int multiSucc()
{
	//baseLineTest();
	//exit(0);



	printf("checkpoint0\n");
	srand(time(0));

	brain * best =generateBasicBrain();//generateXorBrain();
	int rigor = 10000;
	int score = 0;
	int sum =0;
	int counter=0;
	int validated = 0;



	brain  ** children = malloc(sizeof(brain * ) * 5);

	while (!validated)
	{
		//		printf("checkpoint1\n");

		for(int i = 0 ; i < 5; i ++)
		{

			children[i] = forkBrain(best);
			mutateBrain(children[i]);
		}

		int childScore = 0;
		brain * bestChild;	

		for(int i = 0 ; i < 5; i++ )
		{
			brain * candidate = forkBrain(best);

			//		printf("checkpoint1.5\n");

			mutateBrain(candidate);




			//brain * testInstance = forkBrain(candidate);
			//		printf("checkpoint1.75\n");

			//		int newScore = evaluateXorPerformance(testInstance, rigor);
			//			printf("NEW SCORE: %d\n" , newScore);


			int newChildScore = evaluateXorPerformance(candidate,rigor);
			if (newChildScore >  childScore)
			{
				printf("CHILD ACCEPTED: %d\n", newChildScore);
				childScore = newChildScore;
				bestChild = candidate;

			}
		}
		if (childScore >= score)
		{

			printf("NEW BEST SCORE: %d\n" , childScore);
			score = childScore;
			freeBrain(best);
			best =bestChild;
			//printBrain(best);
			validated = (rigor == score);

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

//		multiSucc();
//		exit(0);

	printf("checkpoint0\n");
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


		int newScore = evaluateXorPerformance(testInstance,rigor);

		if (newScore > score)
		{

			printf("NEW BEST SCORE: %d\n" , newScore);
			score = newScore;
			freeBrain(best);
			best =candidate;
			//printBrain(best);
			validated = (4 == score);

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


	return 0;
}
