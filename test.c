#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"brain.h"
#include"xor.h"


//really basic tests

int main (int argc, char *  argv[])
{



// this tests our existing xor code
// might get stuck sometimes with current techniques

printf("VERIFYING PREMADE XOR NETWORK\n");
assert(baseLineXorTest());
printf("PREMADE XOR NETWORK VERIFIED\n");

printf("GENERATE RANDOM NETWORK , TRAIN ON XOR WITH SINGLE SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
xorLearn();


printf("GENERATE RANDOM NETWORK , TRAIN ON XOR WITH MULTI SUCCESSOR TECHNIQUE, OPEN ANALYSIS DIALOG\n");
xorMultiSucc();






exit(0);
}
