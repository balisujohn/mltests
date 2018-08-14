#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<assert.h>
#include"brain.h"
#include"utils.h"

//John Balis 2018
//for support email balisujohn@gmail.com



/*
copies an existing brain, preserving state;
*/
brain * forkBrain(brain * oldBrain)
{
	brain * b  = malloc(sizeof(brain));
	b->neuronCount = oldBrain->neuronCount;
	b->neurons = malloc(sizeof(neuron) * oldBrain->neuronCount);
	for(int i = 0; i < oldBrain->neuronCount; i++)
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

/*
frees a brain struct

*/
void freeBrain(brain * b )
{


	for(int i = 0 ; i < b->neuronCount; i++)

	{
		free(b->neurons[i].potentialWeights);
		free(b->neurons[i].potentialTimes);
		free(b->neurons[i].targets);

	}

	free(b->neurons);
	free(b);
}



/*
initializes a random neuron. requires the number of other neurons as
a range for selecting targets
*/

void initializeNeuron(neuron * n,  int neuronCount )
{
	n->fired = 0;	
	n->age=0;
	n->activationPotential = randFloat();//randFloat();;
	n->excitation = 0.0 ;//randFloat();
	n->activationDuration=0.05;
	n->mostRecentActivation= -100.0;
	n->targetCount = randRange(neuronCount-1)/2;
	n->targets = malloc(sizeof(int)* (n->targetCount));


	for (int c = 0; c < n->targetCount;c++)
	{

		//	do
		//	{ 
		n->targets[c] = randRange(neuronCount-1)+1;
		//	}
		//	while(n->targets[c] == i || ((i ==0 || i == 1) && n->targets[c] ==neuronCount-1)); 


	}



	n->potentialWeights = malloc(sizeof(float) * (neuronCount-1));
	n->potentialTimes = malloc(sizeof(float) * (neuronCount-1));
	for (int c = 0; c < n->targetCount; c ++)
	{
		n->potentialWeights[c] = (randFloat()*2)-1;
		n->potentialTimes[c] = 0.1;
	}



}

/*
allocates and initializes a basic random brain with NEURON_COUNT starting neurons
*/
brain * generateBasicBrain()
{
	assert(NEURON_COUNT > 1);


	brain * b  = malloc(sizeof(brain));
	b->neuronCount = NEURON_COUNT;
	b->neurons = malloc(sizeof(neuron) * NEURON_COUNT);
	for(int i = 0; i < NEURON_COUNT; i++)
	{

		initializeNeuron(&(b->neurons[i]), NEURON_COUNT);
	} 
	return b;

}

/*
generates a brain hardcoded to perform Xor
*/
brain * generateXorBrain()
{
	brain * b  = malloc(sizeof(brain));
	b->neuronCount = 6;
	b->neurons = malloc(sizeof(neuron) * 6);
	for(int i = 0; i < 6; i++)
	{
		b->neurons[i].fired = 0;	
		b->neurons[i].age=0;
		b->neurons[i].activationPotential = 1.0;
		b->neurons[i].excitation = 0.0 ;
		b->neurons[i].activationDuration=0.05;
		b->neurons[i].mostRecentActivation= -100.0;
	} 



	neuron * neurons = b->neurons;


	neurons[0].targetCount = 0;


	neurons[1].targetCount = 2;
	neurons[1].targets = malloc(sizeof(int) *  neurons[1].targetCount);
	neurons[1].potentialWeights = malloc(sizeof(float) * neurons[1].targetCount);
	neurons[1].potentialTimes = malloc(sizeof(float) * neurons[1].targetCount); 
	neurons[1].targets[0] = 4;
	neurons[1].targets[1] = 5;
	neurons[1].potentialWeights[0] =  1.0;
	neurons[1].potentialWeights[1] = -2.0;


	neurons[2].targetCount = 2;
	neurons[2].targets = malloc(sizeof(int) *  neurons[2].targetCount);
	neurons[2].potentialWeights = malloc(sizeof(float) * neurons[2].targetCount);
	neurons[2].potentialTimes = malloc(sizeof(float) * neurons[2].targetCount); 
	neurons[2].targets[0] = 4;
	neurons[2].targets[1] = 5;
	neurons[2].potentialWeights[0] =  -2.0;
	neurons[2].potentialWeights[1] = 1.0;


	neurons[3].targetCount = 0;


	neurons[4].targetCount = 1;
	neurons[4].targets = malloc(sizeof(int) *  neurons[4].targetCount);
	neurons[4].potentialWeights = malloc(sizeof(float) * neurons[4].targetCount);
	neurons[4].potentialTimes = malloc(sizeof(float) * neurons[4].targetCount); 
	neurons[4].targets[0] = 3;
	neurons[4].potentialWeights[0] =  1.0;


	neurons[5].targetCount = 1;
	neurons[5].targets = malloc(sizeof(int) *  neurons[5].targetCount);
	neurons[5].potentialWeights = malloc(sizeof(float) * neurons[5].targetCount);
	neurons[5].potentialTimes = malloc(sizeof(float) * neurons[5].targetCount); 
	neurons[5].targets[0] = 3;
	neurons[5].potentialWeights[0] =  1.0;





	return b;

}


/*
randomly mutates a brain. TODO add mutation params
*/

void mutateBrain(brain * b, int minInputCount, int minOutputCount){


	for(int i = 0 ; i < b->neuronCount; i++)
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
					b->neurons[i].targets[b->neurons[i].targetCount-1] = randRange(b->neuronCount);
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
				b->neurons[i].targets[randRange(b->neurons[i].targetCount)] = randRange(b->neuronCount);
			}

		}
		else if(coinFlip() * coinFlip() )
		{
			b->neurons[i].targetCount++;
			b->neurons[i].targets = realloc(b->neurons[i].targets, sizeof(int) * b->neurons[i].targetCount);
			b->neurons[i].potentialWeights = realloc(b->neurons[i].potentialWeights,sizeof(float) * b->neurons[i].targetCount);
			b->neurons[i].potentialTimes = realloc(b->neurons[i].potentialTimes,sizeof(float) * b->neurons[i].targetCount);
			b->neurons[i].targets[b->neurons[i].targetCount-1] = randRange(b->neuronCount);
			b->neurons[i].potentialWeights[b->neurons[i].targetCount-1]  = (randFloat()*2)-1;


		}
	}


	for(int i = 0 ; i < b->neuronCount; i++)
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



	if(coinFlip() * coinFlip() * coinFlip())
	{
		if(coinFlip())
		{
			b->neuronCount++;
			b->neurons = realloc(b->neurons, sizeof(neuron) * b->neuronCount);
			initializeNeuron(&(b->neurons[b->neuronCount-1]), b->neuronCount);
		}	
		else if(b->neuronCount > 1 + minInputCount +  minOutputCount) 
		{
			b->neuronCount--;
			b->neurons = realloc(b->neurons, sizeof(neuron)* b->neuronCount);

		}



	}

}

/*
applies inputs to a brain. inputs will be applied to neurons 1-targetCount

*/

void inputBrain(brain * b, int * inputs, int targetCount)
{

	assert(targetCount <= b->neuronCount-1);

	b->neurons[0].excitation = b->neurons[0].activationPotential + 1;// here we activate the bias neuron

	for(int i = 1; i < targetCount +1; i++) // the offsets here are to account for the bias node
	{

		b->neurons[i].excitation = inputs[i-1] * (b->neurons[i].activationPotential + 1) ;

	}

}

/*
advances the brain forward 1 discrete fram of time

*/
void advanceBrain(brain * b, int  inputs[], int inputCount, int  outputs[], int outputCount)
{

	//if we've been passed a brain with too few neurons we will do nothing

	assert(! (b->neuronCount < inputCount+outputCount+1));


	inputBrain(b,inputs, inputCount);

	float * sums = malloc(sizeof(float) * b->neuronCount);
	for(int i = 0; i < b->neuronCount;i++)
	{
		sums[i] = 0.0;
	}

	for(int i = 0; i < b->neuronCount; i++)
	{
		b->neurons[i].fired = 0;
		if (mytanh(b->neurons[i].excitation) > b->neurons[i].activationPotential ){ // TODO: Think about the gate function (mytanh)
			for(int c = 0; c < b->neurons[i].targetCount; c++)
			{


				if(b->neurons[i].targets[c] < b->neuronCount)
				{
					sums[b->neurons[i].targets[c]] += b->neurons[i].potentialWeights[c];

				}
			}
			b->neurons[i].excitation = 0.0;	
			b->neurons[i].fired = 1;

		}

	}

	for(int i = 0; i < b->neuronCount; i++)
	{
		for(int c = 0; c < b->neurons[i].targetCount; c++)
		{

			if(b->neurons[i].targets[c] < b->neuronCount)
			{
				b->neurons[b->neurons[i].targets[c]].excitation += sums[b->neurons[i].targets[c]];
			}
		}

	}




	assert(outputCount + inputCount +1 <= b->neuronCount);
	int start = inputCount +1;
	for (int i = 0; i < outputCount; i++)
	{
		outputs[i] = b->neurons[start+i].fired;
	}
}


/*
displays a brain's structure and weights


*/
void printBrain(brain * b ){
	printf("ACTIVATION: ");
	for(int i = 0; i < b->neuronCount; i++)
	{
		printf("%d", b->neurons[i].fired);	
	}
	printf("\n");	
	for(int i = 0; i < b->neuronCount; i++)
	{
		printf("NEURON %d: %f\n",i, b->neurons[i].activationPotential);	
		for(int c = 0; c < b->neurons[i].targetCount; c++)
		{
			printf("TARGET: %d, WEIGHT :%f\n",b->neurons[i].targets[c],b->neurons[i].potentialWeights[c]);

		}	
	}



}

/*
saves a brain to file

*/
void printBrainToFile(brain * b ,FILE * fp){
	fprintf(fp, "ACTIVATION: ");
	for(int i = 0; i < b->neuronCount; i++)
	{
		fprintf(fp,"%d", b->neurons[i].fired);	
	}
	printf("\n");	
	for(int i = 0; i < b->neuronCount; i++)
	{
		fprintf(fp, "NEURON %d: %f\n",i, b->neurons[i].activationPotential);	
		for(int c = 0; c < b->neurons[i].targetCount; c++)
		{
			fprintf(fp,"TARGET: %d, WEIGHT :%f\n",b->neurons[i].targets[c],b->neurons[i].potentialWeights[c]);

		}	
	}



}


