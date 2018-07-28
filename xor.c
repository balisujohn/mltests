#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"brain.h"


//brain freeing will need to be added, as this program is currently going to hemmorage memory

int evaluateXorPerformance(brain * b , int rigor)
{

	int score = 0;

	for(int i = 0; i < rigor; i ++)	
	{
		brain * testInstance = forkBrain(b);

		//		printf("checkpoint2\n");
		int x1 = (((rand()/2)-rand())>1);
		int x2 = (((rand()/2)-rand())>1);
		int expectedResult = x1 ^ x2;
		//	printf("X1: %d X2: %d EXPECTED: %d\n", x1, x2, expectedResult);
		int result = 0 ;
		for(int c = 0; c < 10; c++)
		{
			result =  advanceBrain(testInstance, x1, x2);

		}
		freeBrain(testInstance);
		if (result == expectedResult)score++;
	}

	return score;

}

int main (int argc, char * argv[])
{

	printf("checkpoint0\n");
	srand(time(0));

	brain * best = generateBasicBrain();
	int rigor = 100;
	int score = 0;
	int sum =0;
	int counter=0;
	while (score < rigor)
	{
		//		printf("checkpoint1\n");
		brain * candidate = forkBrain(best);

		//		printf("checkpoint1.5\n");

		mutateBrain(candidate);
		brain * testInstance = forkBrain(candidate);
		//		printf("checkpoint1.75\n");

		int newScore = evaluateXorPerformance(testInstance, rigor);
		//		printf("NEW SCORE: %d\n" , newScore);

		if (newScore > score)
		{
			printf("NEW BEST SCORE: %d\n" , newScore);
			score = newScore;
			freeBrain(best);
			best =candidate;	
		}
		sum += newScore;
		counter++;
		if (counter == 1000)
		{
			printf("LAST 1000 AVERAGE: %f\n", sum/1000.0);


			sum = 0;
			counter = 0;
		}
	}






	return 0;
}
