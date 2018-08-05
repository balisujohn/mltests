#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"brain.h"
#include"xor.h"
#include"learning.h"
#include"smath.h"
//really basic tests

int main (int argc, char *  argv[])
{



// this tests our existing xor code
// might get stuck sometimes with current techniques

printf("VERIFYING PREMADE XOR NETWORK\n");
assert(baseLineXorTest());
printf("PREMADE XOR NETWORK VERIFIED\n");




printf("GENERATE RANDOM NETWORK , TRAIN ON IDENTITY WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
learn(evaluateIdentityPerformance,1,1);


printf("GENERATE RANDOM NETWORK , TRAIN ON IDENTITY WITH MULTI SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
multiSucc(evaluateIdentityPerformance,1,1);



/*
printf("GENERATE RANDOM NETWORK , TRAIN ON NOT WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
learn(evaluateNotPerformance,1,1);


printf("GENERATE RANDOM NETWORK , TRAIN ON NOT WITH MULTI SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
multiSucc(evaluateNotPerformance,1,1);

printf("GENERATE RANDOM NETWORK , TRAIN ON AND WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
learn(evaluateAndPerformance,2,1);


printf("GENERATE RANDOM NETWORK , TRAIN ON AND WITH MULTI SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
multiSucc(evaluateAndPerformance,2,1);

printf("GENERATE RANDOM NETWORK , TRAIN ON OR WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
learn(evaluateOrPerformance,2,1);


printf("GENERATE RANDOM NETWORK , TRAIN ON OR WITH MULTI SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
multiSucc(evaluateOrPerformance,2,1);

printf("GENERATE RANDOM NETWORK , TRAIN ON NOR WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
learn(evaluateNorPerformance,2,1);


printf("GENERATE RANDOM NETWORK , TRAIN ON NOR WITH MULTI SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
multiSucc(evaluateNorPerformance,2,1);


printf("GENERATE RANDOM NETWORK , TRAIN ON XOR WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
learn(evaluateXorPerformance,2,1);


printf("GENERATE RANDOM NETWORK , TRAIN ON XOR WITH MULTI SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
multiSucc(evaluateXorPerformance,2,1);

*/

printf("GENERATE RANDOM NETWORK , TRAIN ON ADDITION WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
learn(evaluateAdditionPerformance,6,4);






exit(0);
}
