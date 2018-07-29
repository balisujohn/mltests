#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"brain.h"
#include"utils.h"




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
		//			printf("X0: %d X2: %d EXPECTED: %d\n", x1, x2, expectedResult);
		int result = 0 ;
		for(int c = 0; c < 3; c++)
		{
			result = advanceBrain(testInstance, x1*(c==0),x2*(c==0) );
			//	printBrain(testInstance);
			//printBrain(testInstance);

		}
		freeBrain(testInstance);
		if (result==1/*expectedResult*/)score++;
	}

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


/*
   int multiSuccessor ()
   {
//	baseLineTest();
//	exit(0);



printf("checkpoint0\n");
srand(time(0));

brain * best = generateBasicBrain();//generateXorBrain();
int rigor = 100;
int score = 0;
int sum =0;
brain * children = malloc(sizeof(brain * ) * 1000);
int counter=0;
int validated = 0;
while (!validated)
{
int newScore = 0;
for (int i = 0; i < 1000; i ++)
{
//		printf("checkpoint1\n");
children[i] = forkBrain(best);

//		printf("checkpoint1.5\n");

mutateBrain(children[i]);
brain * testInstance = forkBrain(children[i]);
//		printf("checkpoint1.75\n");

newScore = evaluateXorPerformance(testInstance, rigor);
}		printf("NEW SCORE: %d\n" , newScore);

if (newScore > score)
{
//			printf("NEW BEST SCORE: %d\n" , newScore);
score = newScore;
freeBrain(best);
best =candidate;
printBrain(best);
validated = (10000 == evaluateXorPerformance(best,10000));
printf("VALIDATION RUN: %d\n" ,  evaluateXorPerformance(best,10000));

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






return 0;
}
 */
int main (int argc, char * argv[])
{
	//	baseLineTest();
	//	exit(0);



	printf("checkpoint0\n");
	srand(time(0));

	brain * best = /*generateBasicBrain();*/generateXorBrain();
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

		int newScore = evaluateXorPerformance(testInstance, rigor);
		//			printf("NEW SCORE: %d\n" , newScore);

		if (newScore >= score)
		{
			//			printf("NEW BEST SCORE: %d\n" , newScore);
			score = newScore;
			freeBrain(best);
			best =candidate;
			printBrain(best);
			validated = (10000 == evaluateXorPerformance(best,10000));
			printf("VALIDATION RUN: %d\n" ,  evaluateXorPerformance(best,10000));

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






	return 0;
}
