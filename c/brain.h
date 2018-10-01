#ifndef BRAIN_H
#define BRAIN_H

#define NEURON_COUNT 11


//John Balis 2018
//for support email balisujohn@gmail.com 



struct mutationParams{
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


struct params{
	char CONTENT_MASK;
	mutationParams  * mParams;
	

}typedef params;

struct neuron{
	float age;
	int targetCount;
	int fired;
	float activationDuration;
	float activationPotential;
	float excitation;
	float mostRecentActivation;
	int * targets;
	float * potentialWeights;
	float * potentialTimes;
} typedef neuron;

struct brain{
	neuron * neurons;
	int neuronCount;
	float age;
} typedef brain;


params * initializeDefaultParams();
brain * generateBasicBrain();
brain * generateSparseBrain();
brain * generateXorBrain();
void mutateBrain(brain * b, mutationParams * m);
void advanceBrain(brain * b, int inputs[], int inputCount,int outputs[], int outputCount);
brain * forkBrain(brain * oldBrain);
void freeBrain(brain * b );
void printBrain(brain * b );
void printBrainToFile(brain * b, FILE * fp); 
mutationParams *  initializeDefaultMutationParams();

#endif
