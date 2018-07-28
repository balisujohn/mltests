#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include"world.h"
#include"hunter.h"
#include"utils.h"

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
			w->zones[i][c].head = malloc(sizeof(object));
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
	printf("-----------------\n");
}


void appendObject(zone * z, object * o)
{

	object * head = z->head;
	o->next = head->next;

	if(o->next)
	{
		o->next->prev = o;
	}
	o->prev = head;
	head->next = o;
	z->objCount++;
}

void removeObject(zone * z, object * o){

	object * curr = z->head->next;
	while(curr)
	{
		if (o == curr)
		{
			o->prev->next = o->next;
			o->prev = NULL;
			o->next = NULL;
			z->objCount--;
			return;
		}

		curr = curr->next;
	}
}


void initializeBasicWorld(world * w)
{
	object * agent = malloc(sizeof(object));
	agent->type = TYPE_AGENT;
	agent->age = w->age;

	int x = randRange(BOARD_SIZE);
	int y = randRange(BOARD_SIZE);

	appendObject(&(w->zones[x][y]),agent);

	w->agentX = x;
	w->agentY = y;

	object * hunter = malloc(sizeof(object));
	hunter->type = TYPE_HUNTER;
	hunter->age = w->age;	

	x = randRange(BOARD_SIZE);
	y = randRange(BOARD_SIZE);
	appendObject(&(w->zones[x][y]),hunter);

}

void advanceObject(world * w, object * o, int x, int y)
{

	if (o->age < w->age)
	{
		switch (o->type) {

			case TYPE_HUNTER:
				printf("ADVANCED HUNTER AT: %d, %d\n", x, y);
				advanceHunter(w,o,x,y);
				break;
			case TYPE_AGENT:
				printf("ADVANCED AGENT AT: %d, %d\n", x, y);	
				break;

		}
		o->age++;

	}

}


void advanceWorldState(world * w)
{
	w->age++;
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			object  * curr = w->zones[i][c].head->next;
			while (curr)
			{
				advanceObject(w, curr, i , c);
				curr = curr->next;
			}
		}


	}

}

