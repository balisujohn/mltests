#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"utils.h"

int randRange(int limit)
{

	return  rand() % limit;

}

float randFloat()
{
return rand() / (float)INT_MAX;

}


