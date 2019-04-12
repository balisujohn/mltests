#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"brains/brain.h"
#include"utils.h"
#include"analysis.h"


//John Balis 2018
//for support email balisujohn@gmail.com



/*

evaluates a brain's performance on binary and,
returns percent correctness


*/
float evaluateAndPerformance(brain * b)
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


	for(int c = 0; c < 5; c++)
	{
		advanceBrain(testInstance, inputs,2, &result, 1);
		advanceBrain(testInstance2, inputs2,2, &result2, 1);
		advanceBrain(testInstance3, inputs3,2, &result3, 1);
		advanceBrain(testInstance4, inputs4,2, &result4, 1);




	}
	freeBrain(testInstance);
	freeBrain(testInstance2);
	freeBrain(testInstance3);
	freeBrain(testInstance4);




	if (result==expectedResult)score++;
	if (result2==expectedResult2)score++;
	if (result3==expectedResult3)score++;
	if (result4==expectedResult4)score++;



	return (score/4.0) * 100;

}

/*

evaluates a brain's performance on binary nor,
returns percent correctness


*/


float evaluateNorPerformance(brain * b )
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
	int expectedResult2 = 1;
	int expectedResult3 = 0;
	int expectedResult4 = 0;


	for(int c = 0; c < 5; c++)
	{
		advanceBrain(testInstance, inputs,2, &result, 1);
		advanceBrain(testInstance2, inputs2,2, &result2, 1);
		advanceBrain(testInstance3, inputs3,2, &result3, 1);
		advanceBrain(testInstance4, inputs4,2, &result4, 1);




	}
	freeBrain(testInstance);
	freeBrain(testInstance2);
	freeBrain(testInstance3);
	freeBrain(testInstance4);




	if (result==expectedResult)score++;
	if (result2==expectedResult2)score++;
	if (result3==expectedResult3)score++;
	if (result4==expectedResult4)score++;



	return (score/4.0) * 100;

}

/*

evaluates a brain's performance on unary identity,
returns percent correctness


*/


float evaluateIdentityPerformance(brain * b )
{
	int score = 0;


	brain * testInstance = forkBrain(b);
	brain * testInstance2 = forkBrain(b);
	
	int result = 0;
	int result2   = 0;

	int inputs[] = { 1 };
	int inputs2[] = { 0 };


	int expectedResult = 1;
	int expectedResult2 = 0;


	for(int c = 0; c < 5; c++)
	{
		advanceBrain(testInstance, inputs,1, &result, 1);
		advanceBrain(testInstance2, inputs2,1, &result2, 1);



	}
	freeBrain(testInstance);
	freeBrain(testInstance2);



	if (result==expectedResult)score++;
	if (result2==expectedResult2)score++;


	return (score/2.0) * 100; // calculated like this for clarity

}

/*

evaluates a brain's performance on unary  not,
returns percent correctness


*/

float evaluateNotPerformance(brain * b)
{
	int score = 0;


	brain * testInstance = forkBrain(b);
	brain * testInstance2 = forkBrain(b);

	int result = 0;
	int result2   = 0;

	int inputs = { 1 };
	int inputs2 = { 0 };


	int expectedResult = 0;
	int expectedResult2 = 1;


	for(int c = 0; c < 5; c++)
	{
		advanceBrain(testInstance, &inputs,1, &result, 1);
		advanceBrain(testInstance2, &inputs2,1, &result2, 1);



	}
	freeBrain(testInstance);
	freeBrain(testInstance2);



	if (result==expectedResult)score++;
	if (result2==expectedResult2)score++;


	return (score/2.0) * 100; // calculated like this for clarity

}


/*

evaluates a brain's performance on binary or,
returns percent correctness


*/


float evaluateOrPerformance(brain * b)
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


	for(int c = 0; c < 5; c++)
	{
		advanceBrain(testInstance, inputs,2, &result, 1);
		advanceBrain(testInstance2, inputs2,2, &result2, 1);
		advanceBrain(testInstance3, inputs3,2, &result3, 1);
		advanceBrain(testInstance4, inputs4,2, &result4, 1);




	}
	freeBrain(testInstance);
	freeBrain(testInstance2);
	freeBrain(testInstance3);
	freeBrain(testInstance4);




	if (result==expectedResult)score++;
	if (result2==expectedResult2)score++;
	if (result3==expectedResult3)score++;
	if (result4==expectedResult4)score++;



	return (score/4.0) * 100;

}

/*

evaluates a brain's performance on binary Xor,
returns percent correctness


*/


float evaluateXorPerformance(brain * b)
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


	for(int c = 0; c < 5; c++)
	{
		advanceBrain(testInstance, inputs,2, &result, 1);
		advanceBrain(testInstance2, inputs2,2, &result2, 1);
		advanceBrain(testInstance3, inputs3,2, &result3, 1);
		advanceBrain(testInstance4, inputs4,2, &result4, 1);

	
	}
	freeBrain(testInstance);
	freeBrain(testInstance2);
	freeBrain(testInstance3);
	freeBrain(testInstance4);




	if (result==expectedResult)score++;
	if (result2==expectedResult2)score++;
	if (result3==expectedResult3)score++;
	if (result4==expectedResult4)score++;



	return (score/4.0 ) * 100.0;

}


//DEPRECATED

/*
verifies that the hardcoded xor network still works. If this is broken, nothing else is guaranteed to work
*/
/*
int  baseLineXorTest()
{
	brain * baseLine = generateXorBrain();
	brain * testInstance = forkBrain(baseLine);
	int output = evaluateXorPerformance(testInstance);
	freeBrain(baseLine);
	freeBrain(testInstance);
	printf("SCORE: %d\n", output);
	return output == 100;



}


p->mParams->initialNeuronCount = 3;

*/
