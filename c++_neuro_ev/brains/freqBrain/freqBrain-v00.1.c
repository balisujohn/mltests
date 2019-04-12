#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "freqBrain.h"
#include "../cJSON/cJSON.h"

//John Balis, Michael Ivanitskiy 2018
//for support email:
// balisujohn@gmail.com 
// mivanits@umich.edu


/*
      #### ##    ## #### ########
       ##  ###   ##  ##     ##
       ##  ####  ##  ##     ##
       ##  ## ## ##  ##     ##
       ##  ##  ####  ##     ##
       ##  ##   ###  ##     ##
      #### ##    ## ####    ##
*/

/*
   copies an existing brain, preserving state;
*/
brain * forkBrain(brain * oldBrain)
{
	brain * b  = (brain *) malloc(sizeof(brain));
	b->neuronCount = oldBrain->neuronCount;
	b->neurons = oldBrain->neurons;
	return b;
}

/*

   sets mutation params to comfortable defaults

 */
mutationParams *  initializeDefaultMutationParams()
{
	mutationParams * m = (mutationParams *) malloc(sizeof(mutationParams));
	m->order = (char *) malloc(sizeof(char) * 6);
	m->order[1] = 'c';
	m->order[1] = 't';
	m->order[2] = 'p';
	m->order[0] = 's';
	//m->order[4] = 'h';
	m->order[4] = '\0';
	m->swapProb = 0.1;
	m->neuronCountProb = 0.125;
	m->neuronCountBias = .5;
	m->targetCountProb = 0.25;
	m->targetCountBias = 0.5;
	m->retargetProb = 0.25;
	m->potentialProb = 0.1;
	m->potentialStrength =0.1;
	m->thresholdProb = 0.1;
	m->thresholdStrength = 0.1;
	m->initialNeuronCount = 10;
	m->targetLimit = 5;
	m->minInputCount = 5;
	m->minOutputCount = 5;
	return m;
}


/*
   sets general params to comfortable defaults
 */
params * initializeDefaultParams()
{
	params * p = (params *) malloc(sizeof(params));
	p->mParams = initializeDefaultMutationParams();
	p->CONTENT_MASK = 0;
	return p;
}

/*
   initializes a random neuron. requires the number of other neurons as
   a range for selecting targets
 */

void initializeNeuron(neuron * n,  int neuronCount , int targetCountLimit = INT_MAX)
{
	*n = neuron(randRange(neuronCount-1)/2, neuronCount);
}

/*
   copies the contents of a neuron into another neuron
 */
void copyNeuron(neuron * original, neuron * replica)
{
	*replica = *original;
}


/*
   allocates and initializes a basic random brain with NEURON_COUNT starting neurons
 */
brain * generateBasicBrain()
{
	// assert(NEURON_COUNT > 1);
	brain * b  = new brain(NEURON_COUNT); 
	return b;
}

/*
   generates a brain with few connections
 */
brain * generateSparseBrain(mutationParams * m)
{
	assert(m->initialNeuronCount > 1);

	brain * b  = new brain(NEURON_COUNT, false);
	return b;
}


/*
      ##     ## ##     ## ########    ###    ######## ########
      ###   ### ##     ##    ##      ## ##      ##    ##
      #### #### ##     ##    ##     ##   ##     ##    ##
      ## ### ## ##     ##    ##    ##     ##    ##    ######
      ##     ## ##     ##    ##    #########    ##    ##
      ##     ## ##     ##    ##    ##     ##    ##    ##
      ##     ##  #######     ##    ##     ##    ##    ########
*/

/*
   randomly mutates a brain.
 */

void mutateBrain(brain * b, mutationParams * m)
{

	//historical presets, preserved for reference

	/*neuronCountMutation( b, minInputCount, minOutputCount, .125, .5);
	  targetMutation(b, .25, .5,.25);
	  potentialsMutation(b, 1, .1);
	  neuronSwapMutation(b, .1);*/

	/*
	   neuronSwapMutation(b, .1);
	   neuronCountMutation( b, minInputCount, minOutputCount, .125, .5);
	   targetMutation(b, .25, .5,.25);
	   potentialsMutation(b, 1, .1);
	   thresholdMutation(b,1,.1);
	 */

	b->mutate(m);
}


/*
       ######  ######## ######## ########
      ##    ##    ##    ##       ##     ##
      ##          ##    ##       ##     ##
       ######     ##    ######   ########
            ##    ##    ##       ##
      ##    ##    ##    ##       ##
       ######     ##    ######## ##
*/


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

	float * sums = (float *) malloc(sizeof(float) * b->neuronCount);
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
			b->neurons[i].fired = 1;
	b->neurons[i].excitation = 0.0;	


		}
		b->neurons[i].excitation = b->neurons[i].excitation/2.0;	


	}

	for(int i = 0; i < b->neuronCount; i++)
	{
	//	for(int c = 0; c < b->neurons[i].targetCount; c++)
	//	{
//
//			if(b->neurons[i].targets[c] < b->neuronCount)
//			{
				b->neurons[i/*b->neurons[i].targets[c]*/].excitation += sums[i/*b->neurons[i].targets[c]*/];
//			}
//		}

	}




	assert(outputCount + inputCount +1 <= b->neuronCount);
	int start = inputCount +1;
	for (int i = 0; i < outputCount; i++)
	{
		outputs[i] = b->neurons[start+i].fired;
	}
	free(sums);
}


/*
      ####       ##  #######
       ##       ##  ##     ##
       ##      ##   ##     ##
       ##     ##    ##     ##
       ##    ##     ##     ##
       ##   ##      ##     ##
      #### ##        #######
*/

/*
                        iii tt
      ww      ww rr rr      tt      eee
      ww      ww rrr  r iii tttt  ee   e
       ww ww ww  rr     iii tt    eeeee
        ww  ww   rr     iii  tttt  eeeee

*/

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
   saves a brain to file. Uses JavaScript Object Notation. format template included in specs folder. 

 */
void printBrainToFile(brain * b ,FILE * fp){


	cJSON * brainJSON = cJSON_CreateObject();
	assert(brainJSON != NULL);
	cJSON * neuronCountJSON = cJSON_CreateNumber(b->neuronCount);	
	assert(neuronCountJSON != NULL);
	cJSON_AddItemToObject(brainJSON, "neuronCount", neuronCountJSON);
	cJSON * neuronsJSON = cJSON_CreateArray();
	assert(neuronsJSON!=NULL);
	for(int i = 0; i < b->neuronCount; i++)
	{
		cJSON * targetsJSON = cJSON_CreateArray();
		assert(targetsJSON!=NULL);
		cJSON * weightsJSON = cJSON_CreateArray();
		assert(weightsJSON!=NULL);
		cJSON * thresholdJSON = cJSON_CreateNumber(b->neurons[i].activationPotential);	
		assert(thresholdJSON!= NULL);
		cJSON * targetCountJSON = cJSON_CreateNumber(b->neurons[i].targetCount);
		assert(targetCountJSON != NULL);
		for(int c = 0; c < b->neurons[i].targetCount; c++)
		{
			cJSON * newTargetJSON = cJSON_CreateNumber(b->neurons[i].targets[c]);
			assert(newTargetJSON!=NULL);
			cJSON_AddItemToArray(targetsJSON,newTargetJSON);
			cJSON * newPotentialJSON = cJSON_CreateNumber(b->neurons[i].potentialWeights[c]);
			assert(newPotentialJSON != NULL);
			cJSON_AddItemToArray(weightsJSON,newPotentialJSON);



		}

		cJSON * newNeuronJSON = cJSON_CreateObject();
		assert(newNeuronJSON != NULL);	
		cJSON_AddItemToObject(newNeuronJSON, "targets", targetsJSON);
		cJSON_AddItemToObject(newNeuronJSON, "weights", weightsJSON);
		cJSON_AddItemToObject(newNeuronJSON, "threshold", thresholdJSON);
		cJSON_AddItemToObject(newNeuronJSON, "targetCount", targetCountJSON);
		cJSON_AddItemToArray(neuronsJSON, newNeuronJSON);
	}

	cJSON_AddItemToObject(brainJSON,"neurons", neuronsJSON);
	char * resultString = NULL;

	resultString = cJSON_Print(brainJSON);


	cJSON_Delete(brainJSON);
	fprintf(fp, "%s", resultString);
	free(resultString);
}


/*
                                 dd
      rr rr    eee    aa aa      dd
      rrr  r ee   e  aa aaa  dddddd
      rr     eeeee  aa  aaa dd   dd
      rr      eeeee  aaa aa  dddddd

*/

brain * loadBrainFromFile(FILE * fp)
{
	fseek(fp, 0L, SEEK_END);
	size_t size = ftell(fp)+1;
	rewind(fp);
	char * stringBuffer = (char *) malloc(sizeof(char) *size);

	fread((void *)stringBuffer, size,1,fp);
	stringBuffer[size-1] = '\0';

	cJSON * brainJSON = cJSON_Parse(stringBuffer);
	assert(brainJSON != NULL);

	brain * b = (brain *) malloc(sizeof(brain));

	cJSON * neuronCountJSON = cJSON_GetObjectItemCaseSensitive(brainJSON, "neuronCount");
	assert(neuronCountJSON!=NULL);
	int neuronCount = neuronCountJSON->valueint;
	b->neuronCount = neuronCount;


	cJSON * neuronsJSON = cJSON_GetObjectItemCaseSensitive(brainJSON, "neurons");
	assert(neuronsJSON!=NULL);

	cJSON * neuronJSON = NULL;

	b->neurons = (neuron *) malloc(sizeof(neuron) * neuronCount);
	int neuronIndex = 0;
	cJSON_ArrayForEach(neuronJSON, neuronsJSON)
	{
		neuron * n = &(b->neurons[neuronIndex++]);
		cJSON * targetCountJSON = cJSON_GetObjectItemCaseSensitive(neuronJSON, "targetCount");
		assert(cJSON_IsNumber(targetCountJSON));
		int targetCount = targetCountJSON->valueint;
		cJSON * thresholdJSON = cJSON_GetObjectItemCaseSensitive(neuronJSON, "threshold");
		float threshold = thresholdJSON->valuedouble;


		n->fired = 0;	
		n->age=0;
		n->activationPotential = threshold;
		n->excitation = 0.0 ;
		n->targetCount = targetCount;

		n->targets = (int *) malloc(sizeof(int)* (n->targetCount));
		n->potentialWeights = (float *) malloc(sizeof(float)* n->targetCount);
		cJSON * targetsJSON = cJSON_GetObjectItemCaseSensitive(neuronJSON, "targets");
		int counter = 0;
		cJSON * targetJSON;
		cJSON_ArrayForEach(targetJSON, targetsJSON)
		{
			n->targets[counter++] = targetJSON->valueint;
		}
		cJSON * weightsJSON = cJSON_GetObjectItemCaseSensitive(neuronJSON, "weights");
		counter = 0;
		cJSON * weightJSON = NULL;
		cJSON_ArrayForEach(weightJSON, weightsJSON)
		{
			n->potentialWeights[counter++] = weightJSON->valuedouble;
		}



	} 

	cJSON_Delete(brainJSON);


	return b;




}
