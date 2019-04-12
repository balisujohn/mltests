#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include <math.h>
#include"utils.h"


//John Balis 2018
//for support email balisujohn@gmail.com



/*
returns 0 - (limit-1)
*/
int randRange(int limit)
{

	return  rand() % limit;

}


/*
This is useful for mapping bits from an int to array indices to prep for inputting a brain.
*/
void mapIntToArray(int value, int * map, int length)
{
for(int i = 0; i < length; i++)
{
map[i] = (value >> i) & 1;
}

}


void mapIntToUnaryArray(int value, int * map, int length)
{
for(int i = 0; i < length; i++)
{
map[i] = (value >> i) > 0;
}

}


/*
Takes a range of an aray of integers such that each integer is equal to one or zero and returns the integer value 
constructed from binary. 

*/
int mapArrayToInt(int * map, int length)
{
int val = 0;
for(int i = 0; i < length; i++)
{
val +=  (map[i] << i);

}

return val;
}



/*
return a random float between 0 and 1

*/
float randFloat()
{

return (float)rand() / (float)RAND_MAX;

}


/*
returns 1 or 0 with a 50-50 probablitiy
*/


int coinFlip()
{
return ((rand()-rand())>0);
}


float sigmoid(float x)
{
     return 1 / (1 + exp((double) -x));
}

float mytanh(float x)
{
	return 2*sigmoid(2*x)-1;
}
