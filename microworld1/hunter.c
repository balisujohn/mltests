#include<stdlib.h>
#include<stdio.h>
#include"world.h"
#include"movement.h"
#include"hunter.h"

//John Balis 2018
//for support email balisujohn@gmail.com 


void advanceHunter(world * w, object * hunter, int x, int y)
{
	int destX, destY;
	moveTowards(x, y, w->agentX, w->agentY, &destX, &destY);
	if(destX != x || destY != y)
	{
		zone * currZone = &(w->zones[x][y]);
		zone * destZone = &(w->zones[destX][destY]);
//		printf("HUNTER\n");
//		printf("REMOVING HUNTER FROM %i, %i\n", x, y);
		removeObject(currZone, hunter );
		appendObject(destZone, hunter);
		
//		printf("ADVANCED HUNTER T0: %d , %d\n" , destX , destY);
	}
}
