#include<stdlib.h>
#include<stdio.h>
#include"world.h"
#include"movement.h"
#include"hunter.h"


void advanceHunter(world * w, object * hunter, int x, int y)
{
	int destX, destY;
	moveTowards(x, y, w->agentX, w->agentY, &destX, &destY);
	if(destX != x || destY != y)
	{
		zone * currZone = &(w->zones[x][y]);
		zone * destZone = &(w->zones[destX][destY]);
		printf("ADVANCED HUNTER T0: %d , %d\n" , destX , destY);
		removeObject(currZone, hunter );
		appendObject(destZone, hunter);
		
	}
}
