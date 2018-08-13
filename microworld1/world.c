#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include"world.h"
#include"hunter.h"
#include"../utils.h"
#include"../brain.h"

//John Balis 2018
//for support email balisujohn@gmail.com


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
			fprintf(stdout,"%d",w->zones[c][i].objCount);
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

	agentInfo * info = malloc(sizeof(agentInfo));
	info-> direction = randRange(4); // for reference, see direction flags in world.h
	info->health = 10;
	agent->objectInfo = (void*)info;

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


int atLocation(world * w, int objectType, int x , int y)
{
	zone * location = &(w->zones[x][y]);
	object * curr = location->head;
	printf("X: %d , Y : %d\n",x ,y);
	while (curr = curr->next)
	{
		if (objectType == TYPE_ANY)
		{
			return 1;
		}
		else if (curr->type == objectType)
		{
			return 1;

		}
	}

	return 0;


}


int painSignal(world * w, int x, int y)
{
	return atLocation(w, TYPE_HUNTER, x, y);
}



/*
   returns the distance to the nearest object, objects occupying the same zone are not visible
*/ 
int lookDistance(world * w, agentInfo * a, int direction, int x, int y)
{


	switch (a->direction){

		case DIRECTION_UP:

			if (y == 0)
			{
			return 1;
			}
			
			for (int i = y-1; i>=0;i--)
			{
				if (atLocation(w,TYPE_ANY,x,i))
				{
				return abs(y-i);
				}
			

			}
			printf("reached\n");
			return y + 1;

			

		case DIRECTION_RIGHT:

			if (x == BOARD_SIZE-1)
			{
			return 1;
			}
			
			for (int i = x +1; i<BOARD_SIZE; i++)
			{
				if (atLocation(w,TYPE_ANY,i,y))
				{
				return abs(x-i);
				}


			}
			printf("reached\n");
			return (BOARD_SIZE-x); 






		case DIRECTION_LEFT:

			if (x == 0)
			{
			return 1;
			}
			
			for (int i = x-1; i>=0;i--)
			{
				if (atLocation(w,TYPE_ANY,i,y))
				{
				return abs(x-i) + 1;
				}


			}
			printf("reached\n");
			return x + 1 ;



		case DIRECTION_DOWN:

			if (y == BOARD_SIZE-1)
			{
			return 1;
			}
			
			for (int i = y+1; i<BOARD_SIZE;i++)
			{
				if (atLocation(w,TYPE_ANY,x,i))
				{
				return abs(y-i);
				}


			}
			printf("reached\n");
			return (BOARD_SIZE-y);





	}


}






void advanceObject(world * w, object * o, brain * b,  int x, int y)
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
				agentInfo * info = (agentInfo *)(o->objectInfo);

				int inputs[4] = {0,0,0,0};  
				int outputs[3] = {0,0,0};

				if (painSignal(w,x,y))
				{
					inputs[0] = 1;
					info->health -= 1;	
				}

				int distance = lookDistance(w, info,info->direction,x,y);
				
				if(distance > 7)
				{
				inputs[1] = 1;
				inputs[2] = 1;
				inputs[3] = 1;
				}
				else
				{

				inputs[1] =(distance >>2) & 1;
				inputs[2] =(distance >>1) & 1;
				inputs[3] =distance  & 1;
				}

				advanceBrain(b,inputs,4,outputs,3);
				
				int outputMode = (outputs[0]) | (outputs[1]<<1) | (outputs[2]<<2);
				printf("DIRECTION: %d\n", info->direction);
				printf("INPUT MODE: ");
				for(int i = 0; i < 4; i++ )
				{
				printf("%d", inputs[i]);
				}
				printf("\n");
				printf("OUTPUT MODE: %d\n", outputMode);
				/*case outputMode{
				


				}
*/
				break;

		}
		o->age++;

	}

}


void advanceWorldState(world * w, brain * b)
{
	w->age++;
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			object  * curr = w->zones[i][c].head->next;
			while (curr)
			{
				advanceObject(w,  curr,b, i , c);
				curr = curr->next;
			}
		}


	}

}

