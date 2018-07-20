#include<stdlib.h>
#include<stdio.h>
#include"world.h"


int randRange(int limit)
{

   return  rand() % limit;

}

world * generateWorld()
{
	world * w = malloc(sizeof(world));
	for(int i = 0; i < boardSize; i++)
	{
		for(int c = 0; c < boardSize; c++)
		{
			w->zones[i][c].objCount = 0;
			w->zones[i][c].objects = NULL;
		}

	}
	return w;
}

void printWorldPop(world * w)
{
	for(int i = 0; i < boardSize; i++)
	{
		for(int c = 0; c < boardSize; c++)
		{
			fprintf(stdout,"%d",w->zones[i][c].objCount);
		}
		fprintf(stdout,"\n");

	}

}



void initializeBasicWorld(world * w)
{
object * agent = malloc(sizeof(agent));
w->zones[randRange(boardSize)][randRange(boardSize)].objects = agent;
w->zones[randRange(boardSize)][randRange(boardSize)].objCount = 1;
agent->type = 1;
}



