#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"brain.h"
#include"xor.h"
#include"learning.h"
#include"smath.h"


//John Balis 2018
//for support email balisujohn@gmail.com


int main (int argc, char *  argv[])
{


params * p = initializeDefaultParams();



p->mParams->initialNeuronCount = 4;

p->mParams->minInputCount = 2;
p->mParams->minOutputCount = 1; 

printf("GENERATE RANDOM NETWORK , TRAIN ON XOR WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
learn(evaluateXorPerformance,p);





p->mParams->minInputCount = 1;
p->mParams->minOutputCount = 1; 

printf("GENERATE RANDOM NETWORK , TRAIN ON IDENTITY WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
learn(evaluateIdentityPerformance,p);


p->mParams->minInputCount = 1;
p->mParams->minOutputCount = 1; 

printf("GENERATE RANDOM NETWORK , TRAIN ON NOT WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
learn(evaluateNotPerformance,p);

p->mParams->minInputCount = 2;
p->mParams->minOutputCount = 1; 

printf("GENERATE RANDOM NETWORK , TRAIN ON AND WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
learn(evaluateAndPerformance,p);


p->mParams->minInputCount = 2;
p->mParams->minOutputCount = 1; 

printf("GENERATE RANDOM NETWORK , TRAIN ON OR WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
learn(evaluateOrPerformance,p);


p->mParams->minInputCount = 2;
p->mParams->minOutputCount = 1; 

printf("GENERATE RANDOM NETWORK , TRAIN ON NOR WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
learn(evaluateNorPerformance,p);


p->mParams->minInputCount = 6;
p->mParams->minOutputCount = 4; 
p->mParams->initialNeuronCount = 100;

printf("GENERATE RANDOM NETWORK , TRAIN ON ADDITION WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
learn(evaluateAdditionPerformance,p);







exit(0);
}
