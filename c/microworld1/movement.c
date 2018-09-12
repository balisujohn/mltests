#include<stdlib.h>
#include<stdio.h>
#include"world.h"


//John Balis 2018
//for support email balisujohn@gmail.com



void moveTowards(int myX, int myY, int targetX, int targetY, int * resultX, int * resultY){

	int xDistance = targetX - myX;
	int yDistance = targetY - myY;

	if (xDistance == 0 && yDistance == 0)
	{
		* resultX = myX;
		* resultY = myY;
		return;
	}
	if (abs(xDistance) > abs(yDistance))
	{
		* resultX = myX + (xDistance / abs(xDistance)) ;
		* resultY = myY;
	}
	else
	{
		* resultX = myX;
		* resultY = myY + (yDistance / abs(yDistance)); 
	}



}

void moveDirection(int myX, int myY, int * resultX, int * resultY, int direction)
{

	switch(direction)
	{
		case DIRECTION_UP:
			if (myY > 0)
			{
				*resultX = myX;
				*resultY = myY-1;
			}
			else
			{
				*resultX = myX;
				*resultY = myY;
			}
			break;
		case DIRECTION_RIGHT:
			if (myX < BOARD_SIZE-1)
			{
				*resultX = myX + 1;
				*resultY = myY;
			}
			else
			{
				*resultX = myX;
				*resultY = myY;
			}

			break;

		case DIRECTION_DOWN:
			if (myY < BOARD_SIZE-1)
			{
				*resultX = myX;
				*resultY = myY+1;
			}
			else
			{
				*resultX = myX;
				*resultY = myY;
			}


			break;

		case DIRECTION_LEFT:
			if (myX >0)
			{
				*resultX = myX-1;
				*resultY = myY;
			}
			else
			{
				*resultX = myX;
				*resultY = myY;
			}

			break;


	} 




}




