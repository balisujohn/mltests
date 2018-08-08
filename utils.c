#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include"utils.h"



/*
returns 0 - (limit-1)
*/
int randRange(int limit)
{

	return  rand() % limit;

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
