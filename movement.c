#include<stdlib.h>
#include<stdio.h>
#include"world.h"

//For now wraparound is not considered, a crafty agent could learn to exploit this,
void moveTowards(int myX, int myY, int targetX, int targetY, int * resultX, int * resultY){

int xDistance = targetX - myX;
int yDistance = targetY - myY;
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
