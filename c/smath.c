#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"brain.h"
#include"utils.h"


//John Balis 2018
//for support email balisujohn@gmail.com



/*
evaluates the correctness of adding two integers each represented by 3 bits
an example input output would be 

001001 -> 0010 which is 1 + 1 = 2 

*/
float evaluateAdditionPerformance(brain * b)
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
			for(int c = 0; c < 6; c++)
			{
				int inputs[] = {  (x1>>2)&1, (x1>>1) &1, x1 & 1,  (x2>>2)&1,( x2>>1)  &1, x2 & 1};
				/*result =*/ advanceBrain(testInstance, inputs,6, result, 4);
				//	printBrain(testInstance);
				//printBrain(testInstance);

			}
			freeBrain(testInstance);

			if (!((result[0] ^ (expectedResult >>3)) & 1 ))score++;
			if (!((result[1] ^ (expectedResult >>2)) & 1 ))score++;
			if (!((result[2] ^ (expectedResult >>1)) & 1 ))score++;
			if (!(( result[3] ^  expectedResult) & 1))score++;
		}
	}

	//	}

	return (score / 256.0) * 100;

}
