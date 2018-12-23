#ifndef BRAIN_H
#define BRAIN_H

#include <vector>

#define NEURON_COUNT 10


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
};

struct neuron
{
	std::vector <conn> targets;
	std::vector <pulse> action_potential;
};

struct brain
{
	std::vector < neuron > neurons;
} typedef brain;


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
