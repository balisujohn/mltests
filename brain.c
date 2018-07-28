#include<stdlib.h>
#include<stdio.h>
#include"brain.h"
#include"utils.h"


//ASSUMPTIONS: brain fully connected except for self-edges
//not tested yet
brain * forkBrain(brain * oldBrain)
{
	brain * b  = malloc(sizeof(brain));
	b->neurons = malloc(sizeof(neuron) * NEURON_COUNT);
	for(int i = 0; i < NEURON_COUNT; i++)
	{

		b->neurons[i].activationPotential =  oldBrain->neurons[i].activationPotential;
		b->neurons[i].excitation = oldBrain->neurons[i].excitation;
		b->neurons[i].targetCount = oldBrain->neurons[i].targetCount;
		b->neurons[i].age=oldBrain->neurons[i].age;
		b->neurons[i].activationDuration=oldBrain->neurons[i].activationDuration;
		b->neurons[i].mostRecentActivation= oldBrain->neurons[i].mostRecentActivation;
		b->neurons[i].targets = malloc(sizeof(int)*( NEURON_COUNT-1));
		//int target = 0;
		for (int c = 0; c < b->neurons[i].targetCount;c++)
		{
			b->neurons[i].targets[c] = oldBrain->neurons[i].targets[c];

		}
		b->neurons[i].potentialWeights = malloc(sizeof(float) * (NEURON_COUNT-1));
		b->neurons[i].potentialTimes = malloc(sizeof(float) * (NEURON_COUNT-1));
		for (int c = 0; c < b->neurons[i].targetCount; c ++)
		{
			b->neurons[i].potentialWeights[c] = oldBrain->neurons[i].potentialWeights[c];
			b->neurons[i].potentialTimes[c] = oldBrain->neurons[i].potentialTimes[c] ;
		}

	}
	return b; 

}


void freeBrain(brain * b )
{


	for(int i = 0 ; i < NEURON_COUNT; i++)

	{
		free(b->neurons[i].potentialWeights);
		free(b->neurons[i].potentialTimes);
		free(b->neurons[i].targets);

	}

	free(b->neurons);
	free(b);
}



//makes a brain
brain * generateBasicBrain()
{
	brain * b  = malloc(sizeof(brain));
	b->neurons = malloc(sizeof(neuron) * NEURON_COUNT);
	for(int i = 0; i < NEURON_COUNT; i++)
	{
		b->neurons[i].age=0;
		b->neurons[i].activationPotential = 1.0;
		b->neurons[i].excitation = 0.0;
		b->neurons[i].activationDuration=0.05;
		b->neurons[i].mostRecentActivation= -100.0;
		b->neurons[i].targetCount = randRange(NEURON_COUNT-1);
		b->neurons[i].targets = malloc(sizeof(int)*(b->neurons[i].targetCount));


		for (int c = 0; c < b->neurons[i].targetCount;c++)
		{

			//if (c == i) target++;
			do
			{ 
				b->neurons[i].targets[c] = randRange(NEURON_COUNT);
			}
			while(b->neurons[i].targets[c] == i);

		}



		b->neurons[i].potentialWeights = malloc(sizeof(float) * (NEURON_COUNT-1));
		b->neurons[i].potentialTimes = malloc(sizeof(float) * (NEURON_COUNT-1));
		for (int c = 0; c < b->neurons[i].targetCount; c ++)
		{
			b->neurons[i].potentialWeights[c] = randFloat() ;
			b->neurons[i].potentialTimes[c] = 0.1;
		}

	} 
	printf("checkpoint0.5\n");
	return b;

}


//for now we're only going to mutate the weights
// assumes the brain is fully connected
void mutateBrain(brain * b){

	for(int i = 0 ; i < NEURON_COUNT; i++)
	{
		if(b->neurons[i].targetCount)
		{
			int mutations = randRange(b->neurons[i].targetCount);
			for (int c = 0 ; c < mutations; c++)
			{
				
				
			//TODO add soft boundary
			
			b->neurons[i].potentialWeights[randRange(b->neurons[i].targetCount-1)] += ((randFloat() *2)-1)*.1;
		//	if(b->neurons[i].potentialWeight)
			}
		}
	}

}



// we're going to ignore temporal stuff as well for the moment
//we're temporarily inputting neuronal activations as inputs
int advanceBrain(brain * b, int x1, int x2)
{
	//float nextAge = b->age + 1;

	//sense(brain * b);
	// for now we will hardcode sensory input
	//	{
	if (x1)
	{		
		b->neurons[0].excitation  = b->neurons[0].activationPotential +1;
	}
	if (x2)
	{		
		b->neurons[1].excitation  = b->neurons[1].activationPotential +1;
	}

	//	}

	int outputFlag = 0;

	for(int i = 0; i < NEURON_COUNT; i++)
	{

		//		if (b->neurons[i].age >= nextAge) continue;
		if (b->neurons[i].excitation > b->neurons[i].activationPotential ){
			if (i == NEURON_COUNT-1)outputFlag = 1;
			b->neurons[i].excitation = 0.0;	
			for(int c = 0; c < b->neurons[i].targetCount; c++)
			{
				b->neurons[b->neurons[i].targets[c]].excitation += b->neurons[i].potentialWeights[b->neurons[i].targets[c]];
			}
		}

	}

	//for now we'll hard code actuation
	//actuate(brain * b )
	//	{

	return outputFlag;

	//	}

}

//planned functions mutate, advance, fork
