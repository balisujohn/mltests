#include<stdlib.h>
#include<stdio.h>
#include"brain.h"
#include"utils.h"
#include<assert.h>

brain * forkBrain(brain * oldBrain)
{
	brain * b  = malloc(sizeof(brain));
	b->neurons = malloc(sizeof(neuron) * NEURON_COUNT);
	for(int i = 0; i < NEURON_COUNT; i++)
	{


		b->neurons[i].fired = oldBrain->neurons[i].fired;
		b->neurons[i].activationPotential =  oldBrain->neurons[i].activationPotential;
		b->neurons[i].excitation = oldBrain->neurons[i].excitation;
		b->neurons[i].targetCount = oldBrain->neurons[i].targetCount;
		b->neurons[i].age=oldBrain->neurons[i].age;
		b->neurons[i].activationDuration=oldBrain->neurons[i].activationDuration;
		b->neurons[i].mostRecentActivation= oldBrain->neurons[i].mostRecentActivation;
		b->neurons[i].targets = malloc(sizeof(int)*( b->neurons[i].targetCount));
		for (int c = 0; c < b->neurons[i].targetCount;c++)
		{
			b->neurons[i].targets[c] = oldBrain->neurons[i].targets[c];

		}
		b->neurons[i].potentialWeights = malloc(sizeof(float) * (b->neurons[i].targetCount));
		b->neurons[i].potentialTimes = malloc(sizeof(float) * (b->neurons[i].targetCount));
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
		b->neurons[i].fired = 0;	
		b->neurons[i].age=0;
		b->neurons[i].activationPotential = randFloat();//randFloat();;
		b->neurons[i].excitation = 0.0 ;//randFloat();
		b->neurons[i].activationDuration=0.05;
		b->neurons[i].mostRecentActivation= -100.0;
		b->neurons[i].targetCount = randRange(NEURON_COUNT-1)/2;
		b->neurons[i].targets = malloc(sizeof(int)*(b->neurons[i].targetCount));


		for (int c = 0; c < b->neurons[i].targetCount;c++)
		{

			do
			{ 
				b->neurons[i].targets[c] = randRange(NEURON_COUNT);
			}
			while(b->neurons[i].targets[c] == i || ((i ==0 || i == 1) && b->neurons[i].targets[c] ==NEURON_COUNT-1)); 


		}



		b->neurons[i].potentialWeights = malloc(sizeof(float) * (NEURON_COUNT-1));
		b->neurons[i].potentialTimes = malloc(sizeof(float) * (NEURON_COUNT-1));
		for (int c = 0; c < b->neurons[i].targetCount; c ++)
		{
			b->neurons[i].potentialWeights[c] = (randFloat()*2)-1;
			b->neurons[i].potentialTimes[c] = 0.1;
		}

	} 
	return b;

}

brain * generateXorBrain()
{
	assert(NEURON_COUNT==5);
	brain * b  = malloc(sizeof(brain));
	b->neurons = malloc(sizeof(neuron) * 5);
	for(int i = 0; i < 5; i++)
	{
		b->neurons[i].fired = 0;	
		b->neurons[i].age=0;
		b->neurons[i].activationPotential = 1.0;
		b->neurons[i].excitation = 0.0 ;
		b->neurons[i].activationDuration=0.05;
		b->neurons[i].mostRecentActivation= -100.0;
		} 

	neuron * neurons = b->neurons;
	neurons[0].targetCount = 2;
	neurons[0].targets = malloc(sizeof(int) *  neurons[0].targetCount);
	neurons[0].potentialWeights = malloc(sizeof(float) * neurons[0].targetCount);
	neurons[0].potentialTimes = malloc(sizeof(float) * neurons[0].targetCount); 
	neurons[0].targets[0] = 2;
	neurons[0].targets[1] = 3;
	neurons[0].potentialWeights[0] =  1.0;
	neurons[0].potentialWeights[1] = -2.0;


	neurons[1].targetCount = 2;
	neurons[1].targets = malloc(sizeof(int) *  neurons[1].targetCount);
	neurons[1].potentialWeights = malloc(sizeof(float) * neurons[1].targetCount);
	neurons[1].potentialTimes = malloc(sizeof(float) * neurons[1].targetCount); 
	neurons[1].targets[0] = 2;
	neurons[1].targets[1] = 3;
	neurons[1].potentialWeights[0] =  -2.0;
	neurons[1].potentialWeights[1] = 1.0;


	neurons[2].targetCount = 1;
	neurons[2].targets = malloc(sizeof(int) *  neurons[2].targetCount);
	neurons[2].potentialWeights = malloc(sizeof(float) * neurons[2].targetCount);
	neurons[2].potentialTimes = malloc(sizeof(float) * neurons[2].targetCount); 
	neurons[2].targets[0] = 4;
	neurons[2].potentialWeights[0] =  1.0;

	neurons[3].targetCount = 1;
	neurons[3].targets = malloc(sizeof(int) *  neurons[3].targetCount);
	neurons[3].potentialWeights = malloc(sizeof(float) * neurons[3].targetCount);
	neurons[3].potentialTimes = malloc(sizeof(float) * neurons[3].targetCount); 
	neurons[3].targets[0] = 4;
	neurons[3].potentialWeights[0] =  1.0;

	neurons[4].targetCount = 0;





	return b;

}




void mutateBrain(brain * b){


	for(int i = 0 ; i < NEURON_COUNT; i++)
	{
		if(b->neurons[i].targetCount)
		{
			if (coinFlip()*coinFlip())
			{




				if(coinFlip)
				{
					b->neurons[i].targetCount++;
					b->neurons[i].targets = realloc(b->neurons[i].targets, sizeof(int) * b->neurons[i].targetCount);
					b->neurons[i].potentialWeights = realloc(b->neurons[i].potentialWeights,sizeof(float) * b->neurons[i].targetCount);
					b->neurons[i].potentialTimes = realloc(b->neurons[i].potentialTimes,sizeof(float) * b->neurons[i].targetCount);
					b->neurons[i].targets[b->neurons[i].targetCount-1] = randRange(NEURON_COUNT);
					b->neurons[i].potentialWeights[b->neurons[i].targetCount-1]  = randFloat();
				}
				else	
				{

					b->neurons[i].targetCount--;
					b->neurons[i].targets = realloc(b->neurons[i].targets, sizeof(int) * b->neurons[i].targetCount);
					b->neurons[i].potentialWeights = realloc(b->neurons[i].potentialWeights,sizeof(float) * b->neurons[i].targetCount);
					b->neurons[i].potentialTimes = realloc(b->neurons[i].potentialTimes,sizeof(float) * b->neurons[i].targetCount);

				}



			}
			if(coinFlip()*coinFlip())
			{
				b->neurons[i].targets[randRange(b->neurons[i].targetCount)] = randRange(NEURON_COUNT);
			}

		}
		else if(coinFlip() * coinFlip() )
		{
			b->neurons[i].targetCount++;
			b->neurons[i].targets = realloc(b->neurons[i].targets, sizeof(int) * b->neurons[i].targetCount);
			b->neurons[i].potentialWeights = realloc(b->neurons[i].potentialWeights,sizeof(float) * b->neurons[i].targetCount);
			b->neurons[i].potentialTimes = realloc(b->neurons[i].potentialTimes,sizeof(float) * b->neurons[i].targetCount);
			b->neurons[i].targets[b->neurons[i].targetCount-1] = randRange(NEURON_COUNT);
			b->neurons[i].potentialWeights[b->neurons[i].targetCount-1]  = (randFloat()*2)-1;


		}
	}


	for(int i = 0 ; i < NEURON_COUNT; i++)
	{
		if(b->neurons[i].targetCount)
		{
			int mutations = randRange(b->neurons[i].targetCount);
			for (int c = 0 ; c < mutations; c++)
			{
				//TODO add soft boundary

				b->neurons[i].potentialWeights[randRange(b->neurons[i].targetCount)] += ((randFloat() *2)-1)*.1;
			}
		}
	}

}

void inputBrain(brain * b, int * inputs, int targetCount)
{

	assert(targetCount <= NEURON_COUNT);
	for(int i = 0; i < targetCount; i++)
	{
		
		b->neurons[i].excitation = inputs[i] * (b->neurons[i].activationPotential + 1) ;

	}

}


void advanceBrain(brain * b, int  inputs[], int inputCount, int  outputs[], int outputCount)
{
	inputBrain(b,inputs, 2);

	float * sums = malloc(sizeof(float) * NEURON_COUNT);
	for(int i = 0; i < NEURON_COUNT;i++)
	{
		sums[i] = 0.0;
	}

	for(int i = 0; i < NEURON_COUNT; i++)
	{
		b->neurons[i].fired = 0;
		if (b->neurons[i].excitation > b->neurons[i].activationPotential ){
			for(int c = 0; c < b->neurons[i].targetCount; c++)
			{
			 sums[b->neurons[i].targets[c]] += b->neurons[i].potentialWeights[c];
			}
			b->neurons[i].excitation = 0.0;	
			b->neurons[i].fired = 1;

		}

	}

	for(int i = 0; i < NEURON_COUNT; i++)
	{
		for(int c = 0; c < b->neurons[i].targetCount; c++)
		{
			b->neurons[b->neurons[i].targets[c]].excitation += sums[b->neurons[i].targets[c]];
		}

	}



	assert(outputCount <= NEURON_COUNT);
	int start = NEURON_COUNT - outputCount;
	for (int i = 0; i < outputCount; i++)
	{
	outputs[i] = b->neurons[start+i].fired;
	}
}



void printBrain(brain * b ){
	printf("ACTIVATION: ");
	for(int i = 0; i < NEURON_COUNT; i++)
	{
		printf("%d", b->neurons[i].fired);	
	}
	printf("\n");	
	for(int i = 0; i < NEURON_COUNT; i++)
	{
		printf("NEURON %d: %f\n",i, b->neurons[i].activationPotential);	
		for(int c = 0; c < b->neurons[i].targetCount; c++)
		{
			printf("TARGET: %d, WEIGHT :%f\n",b->neurons[i].targets[c],b->neurons[i].potentialWeights[c]);

		}	
	}



}


void printBrainToFile(brain * b ,FILE * fp){
	fprintf(fp, "ACTIVATION: ");
	for(int i = 0; i < NEURON_COUNT; i++)
	{
		fprintf(fp,"%d", b->neurons[i].fired);	
	}
	printf("\n");	
	for(int i = 0; i < NEURON_COUNT; i++)
	{
		fprintf(fp, "NEURON %d: %f\n",i, b->neurons[i].activationPotential);	
		for(int c = 0; c < b->neurons[i].targetCount; c++)
		{
			fprintf(fp,"TARGET: %d, WEIGHT :%f\n",b->neurons[i].targets[c],b->neurons[i].potentialWeights[c]);

		}	
	}



}



