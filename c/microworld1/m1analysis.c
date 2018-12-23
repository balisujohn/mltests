#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"world.h"
#include"../brains/brain.h"
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


		struct timespec interval;
                interval.tv_sec = 0;
                interval.tv_nsec = 200000000;
                nanosleep(&interval, NULL);

			printf("\033[2J");
			advanceWorldState(w,testInstance);
			printWorldInfo(w);

	}





}


