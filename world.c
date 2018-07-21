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
	w->agentX = -1;
	w->agentY = -1;
	w->age = 0;
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			w->zones[i][c].objCount = 0;
			w->zones[i][c].objects = malloc(sizeof(object));
		}

	}
	return w;
}

void printWorldPop(world * w)
{
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			fprintf(stdout,"%d",w->zones[i][c].objCount);
		}
		fprintf(stdout,"\n");

	}

}


void appendObject(zone * z, object * o)
{
	object * curr = z->objects;
	while (curr->next)curr = curr->next;
	curr->next = o;
	z->objCount++;
}


void initializeBasicWorld(world * w)
{
	object * agent = malloc(sizeof(object));
	agent->type = TYPE_AGENT;


	int x = randRange(BOARD_SIZE);
	int y = randRange(BOARD_SIZE);

	appendObject(&(w->zones[x][y]),agent);

	w->agentX = x;
	w->agentY = y;

	object * hunter = malloc(sizeof(object));
	hunter->type = TYPE_HUNTER;

	x = randRange(BOARD_SIZE);
	y = randRange(BOARD_SIZE);
	appendObject(&(w->zones[x][y]),hunter);

}

void advanceObject(world * w, object * o, int x, int y)
{

	switch (o->type) {

		case TYPE_HUNTER:
			printf("ADVANCED HUNTER AT: %d, %d\n", x, y);
			break;
		case TYPE_AGENT:
			printf("ADVANCED AGENT AT: %d, %d\n", x, y);	
			break;

	}


}


void advanceWorldState(world * w)
{
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			object  * curr = w->zones[i][c].objects;
			while (curr)
			{
				advanceObject(w, curr, i , c);
				curr = curr->next;
			}
		}


	}

}

