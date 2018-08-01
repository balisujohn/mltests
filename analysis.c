#include<stdio.h>
#include<stdlib.h>
#include"brain.h"



// needs to be fixed
void analyzeBrain(brain * b , int inputCount, int outputCount)
{

	int run = 1;

	char * userInputs = malloc(sizeof(char)* inputCount);
	int * inputs = malloc(sizeof(int) * inputCount);
	int * outputs = malloc(sizeof(int)* outputCount);
	char userInputField[20];
	

	while(run)
	{

		brain * testInstance = forkBrain(b);
		printf("PLEASE ENTER A STRING SPECIFYING %d INPUTS\n", inputCount);
		fgets(userInputs, inputCount, stdin);
		for(int i = 0; i < inputCount; i++)
		{
			if (userInputs[i] == '1') inputs[i] == 1;
			else if (userInputs[i] == '0') inputs[i] == 0;
			else
			{
				printf("INPUT STRING INVALID, RESTARTING\n");
				free(b);
				continue;
			}

		}
		fgets(userInputField, 20, stdin);
		int advanceTo = atoi(userInputField);
		for(int i = 0; i < advanceTo; i++)
		{
		advanceBrain(testInstance, inputs, inputCount, outputs, outputCount);
		}


		printf("OUTPUTS:");
		for(int i = 0 ; i < outputCount; i ++)
		{
			printf("%d",outputs[i]);
		}
		
		
	}






}
