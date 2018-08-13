#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"world.h"
#include"../brain.h"
//John Balis 2018
//for support email balisujohn@gmail.com 

int main(int arc, char * argv[])
{

srand(time(0));

world * w = generateWorld();
brain * b = generateBasicBrain();
printWorldPop(w);
initializeBasicWorld(w);
printWorldPop(w);
advanceWorldState(w,b);
printWorldPop(w);

advanceWorldState(w,b);
printWorldPop(w);
advanceWorldState(w,b);
printWorldPop(w);
advanceWorldState(w,b);
printWorldPop(w);
advanceWorldState(w,b);
printWorldPop(w);
advanceWorldState(w,b);
printWorldPop(w);
advanceWorldState(w,b);
printWorldPop(w);


exit(0);
}
