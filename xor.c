#include<stdlib.h>
#include<stdio.h>
#include"brain.h"


//brain freeing will need to be added, as this program is currently going to hemmorage memory

int evaluateXorPerformance(brain * b , int rigor)
{

	int score = 0;

	for(int i = 0; i < rigor; i ++)	
	{
//		printf("checkpoint2\n");
		int x1 = ((rand()/2)-rand()>1);
		int x2 = ((rand()/2)-rand()>1);
		int expectedResult = x1 ^ x2;
		int result;
		for(int c = 0; c < 1; c++)
		{
			result = advanceBrain(b, x1, x2);
		}
		if (result == expectedResult)score++;
	}

	return score;

}

int main (int argc, char * argv[])
{

	printf("checkpoint0\n");


	brain * best = generateBasicBrain();
	int rigor = 10000;
	int score = 0;
	while (score < rigor)
	{
//		printf("checkpoint1\n");
		brain * candidate = forkBrain(best);
		
//		printf("checkpoint1.5\n");

		mutateBrain(candidate);
		brain * testInstance = forkBrain(candidate);
//		printf("checkpoint1.75\n");

		int newScore = evaluateXorPerformance(testInstance, rigor);
		printf("NEW SCORE: %d\n" , newScore);

		if (newScore > score)
		{
			printf("NEW BEST SCORE: %d\n" , newScore);
			score = newScore;
			best =candidate;	
		}
	}






	return 0;
}
