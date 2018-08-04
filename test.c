#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"brain.h"
#include"xor.h"
#include"learning.h"

//really basic tests

int main (int argc, char *  argv[])
{



// this tests our existing xor code
// might get stuck sometimes with current techniques

printf("VERIFYING PREMADE XOR NETWORK\n");
assert(baseLineXorTest());
printf("PREMADE XOR NETWORK VERIFIED\n");

printf("GENERATE RANDOM NETWORK , TRAIN ON XOR WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
learn(evaluateXorPerformance,2,1);


printf("GENERATE RANDOM NETWORK , TRAIN ON XOR WITH MULTI SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
multiSucc(evaluateXorPerformance,2,1);






exit(0);
}
