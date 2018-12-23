#ifndef BRAIN_H
#define BRAIN_H

#include <vector>
#include "../utils.h"


// #define NEURON_COUNT 10

int NEURON_COUNT = 10;


//John Balis, Michael Ivanitskiy 2018
//for support email:
// balisujohn@gmail.com 
// mivanits@umich.edu


struct mutationParams
{
	char * order;
	float swapProb;
	float neuronCountProb;
	float neuronCountBias;
	float targetCountProb;
	float targetCountBias;
	float retargetProb;
	float potentialProb;
	float potentialStrength;
	float thresholdProb;
	float thresholdStrength;
	int initialNeuronCount;
	int targetLimit;
	int minInputCount;
	int minOutputCount;
}typedef mutationParams;


struct params
{
	char CONTENT_MASK;
	mutationParams  * mParams;
}typedef params;

struct pulse
{
	float amplitude;
	int period;
	int phaseShift;
};

struct conn
{
	float weight;
	int target;

	conn(float in_wgt, int in_tgt)
		: weight(in_wgt), target(in_tgt) {}
};

struct neuron
{
public:
	std::vector <conn> targets;
	std::vector <pulse> actionPotential;

	// rand ctor
	neuron(int targetCount, int neuronCount)
	{
		targets.reserve(targetCount);

		for (int i = 0; i < targetCount; i++)
		{
			targets.emplace_back((randFloat()*2)-1, randRange(neuronCount-1)+1);
		}
	}

	// empty ctor
};

struct brain
{
	int neuronCount;
	std::vector < neuron > neurons;

	// gen basic
	brain(int in_neuronCount, bool use_rand = true) : neuronCount(in_neuronCount)
	{
		neurons.reserve(neuronCount);

		if (use_rand)
		{
			for(int i = 0; i < neuronCount; i++)
			{
				neurons.emplace_back(randRange(neuronCount-1)/2, neuronCount);
			}
		}
		else
		{
			// if not random connections, then generate a sparse tree w/ no connections
			for(int i = 0; i < neuronCount; i++)
			{
				neurons.emplace_back(0, neuronCount);
			}
		}
	}
};


params * initializeDefaultParams();
brain * generateBasicBrain();
brain * generateSparseBrain(mutationParams * m);
brain * generateXorBrain();
void mutateBrain(brain * b, mutationParams * m);
void advanceBrain(brain * b, int inputs[], int inputCount,int outputs[], int outputCount);
brain * forkBrain(brain * oldBrain);
void freeBrain(brain * b );
void printBrain(brain * b );
void printBrainToFile(brain * b, FILE * fp); 
brain * loadBrainFromFile(FILE * fp);
mutationParams *  initializeDefaultMutationParams();

#endif
