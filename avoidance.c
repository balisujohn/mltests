#include<stdlib.h>
#include<stdio.h>
#include"world.h"



int main(int arc, char * argv[])
{

world * w = generateWorld();
printWorldPop(w);
initializeBasicWorld(w);
printWorldPop(w);
advanceWorldState(w);
printWorldPop(w);








exit(0);
}
