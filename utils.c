#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include"utils.h"

int randRange(int limit)
{

	return  rand() % limit;

}

float randFloat()
{

return (float)rand() / (float)RAND_MAX;

}


