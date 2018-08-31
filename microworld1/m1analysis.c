#include<stdlib.h>
#include<stdio.h>
#include"world.h"
#include"../brain.h"
//John Balis 2018
//for support email balisujohn@gmail.com 

void analyzeBrainMicroWorld1(brain * b)
{
	int run = 1;
	brain * testInstance = forkBrain(b);
	char userInput;
	world * w = generateWorld();
	initializeBasicWorld(w);
	printf("WORLD STARTING STATE\n");
	printWorldInfo(w);
	while(run)
	{
	

		userInput = fgetc(stdin);

		if (userInput=='q')
		{
			break;
		}	
	advanceWorldState(w,testInstance);
	printWorldInfo(w);
	

	}





}


