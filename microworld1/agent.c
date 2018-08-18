#include<stdlib.h>
#include<stdio.h>
#include"world.h"
#include"movement.h"
#include"agent.h"

//John Balis 2018
//for support email balisujohn@gmail.com 


void moveAgent(world * w, object * agent, int x, int y, int direction)
{
	int destX, destY;
	//moveTowards(x, y, w->agentX, w->agentY, &destX, &destY);
	moveDirection(x,y, &destX, &destY, direction);	
	if(destX != x || destY != y)
	{
		zone * currZone = &(w->zones[x][y]);
		zone * destZone = &(w->zones[destX][destY]);
		printf("ADVANCED AGENT T0: %d , %d\n" , destX , destY);
		removeObject(currZone, agent );
		appendObject(destZone, agent);
		
	}
}
