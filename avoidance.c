#include<stdlib.h>
#include<stdio.h>
#include"world.h"

//John Balis 2018
//for support email balisujohn@gmail.com 

int main(int arc, char * argv[])
{

world * w = generateWorld();
printWorldPop(w);
initializeBasicWorld(w);
printWorldPop(w);
advanceWorldState(w);
printWorldPop(w);
advanceWorldState(w);
advanceWorldState(w);
advanceWorldState(w);
advanceWorldState(w);
advanceWorldState(w);
advanceWorldState(w);
advanceWorldState(w);
printWorldPop(w);

exit(0);
}
