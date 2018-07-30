#ifndef BRAIN_H
#define BRAIN_H

#define NEURON_COUNT 25

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
float age;
} typedef brain;

brain * generateBasicBrain();
brain * generateXorBrain();
void mutateBrain(brain * b);
void advanceBrain(brain * b, int inputs[], int inputCount,int outputs[], int outputCount);
brain * forkBrain(brain * oldBrain);
void freeBrain(brain * b );
void printBrain(brain * b );
void printBrainToFile(brain * b, FILE * fp);


#endif
