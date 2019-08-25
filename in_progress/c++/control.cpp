

extern "C"{
#include<stdio.h>
#include "../c/utils.h"
#include "../c/cJSON/cJSON.h"
#include "../c/brain.h"
}


extern "C"{
struct brain * generateBasicBrain();
void printBrain(struct brain * b);
}


int main()
{
struct brain * b  = generateBasicBrain();
printBrain(b);
return(0);
}



