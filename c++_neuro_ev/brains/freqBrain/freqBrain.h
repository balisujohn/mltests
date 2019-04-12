#ifndef BRAIN_H
#define BRAIN_H

#include <vector>
#include <algorithm>
#include "../utils.h"


// John Balis, Michael Ivanitskiy 2018
// for support email:
// balisujohn@gmail.com 
// mivanits@umich.edu

/*
      ##     ## ##     ## ########         ########     ###    ########     ###    ##     ##  ######
      ###   ### ##     ##    ##            ##     ##   ## ##   ##     ##   ## ##   ###   ### ##    ##
      #### #### ##     ##    ##            ##     ##  ##   ##  ##     ##  ##   ##  #### #### ##
      ## ### ## ##     ##    ##            ########  ##     ## ########  ##     ## ## ### ##  ######
      ##     ## ##     ##    ##            ##        ######### ##   ##   ######### ##     ##       ##
      ##     ## ##     ##    ##            ##        ##     ## ##    ##  ##     ## ##     ## ##    ##
      ##     ##  #######     ##    ####### ##        ##     ## ##     ## ##     ## ##     ##  ######
*/


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


/*
       ######  ######## ########  ##     ##  ######  ########  ######
      ##    ##    ##    ##     ## ##     ## ##    ##    ##    ##    ##
      ##          ##    ##     ## ##     ## ##          ##    ##
       ######     ##    ########  ##     ## ##          ##     ######
            ##    ##    ##   ##   ##     ## ##          ##          ##
      ##    ##    ##    ##    ##  ##     ## ##    ##    ##    ##    ##
       ######     ##    ##     ##  #######   ######     ##     ######
*/

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

	// searches "targets" for the given target, and scrambles that target
	void randomize_for(int target, int neuronCount)
	{
		for (conn c : targets)
		{
			if (c.target == target)
			{
				c.target = randRange(neuronCount); 
				// randomizes edges which previously targeted neuron being removed 
			}
		}
	}
};


/*
      ########  ########     ###    #### ##    ##
      ##     ## ##     ##   ## ##    ##  ###   ##
      ##     ## ##     ##  ##   ##   ##  ####  ##
      ########  ########  ##     ##  ##  ## ## ##
      ##     ## ##   ##   #########  ##  ##  ####
      ##     ## ##    ##  ##     ##  ##  ##   ###
      ########  ##     ## ##     ## #### ##    ##
*/

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

/*
                             tt            tt    iii
         mm mm mmmm  uu   uu tt      aa aa tt         oooo  nn nnn
         mmm  mm  mm uu   uu tttt   aa aaa tttt  iii oo  oo nnn  nn
         mmm  mm  mm uu   uu tt    aa  aaa tt    iii oo  oo nn   nn
         mmm  mm  mm  uuuu u  tttt  aaa aa  tttt iii  oooo  nn   nn

*/

	void mutate(mutationParams * m)
	{
		char c;
		int i = 0;
		while((c = (m->order)[i]) != '\0')
		{
			i += 1;
			switch (c) 
			{
				case 's' :
					// swapping handled in neuronCountMutation 
					// neuronSwapMutation(m->swapProb);
					break;

				case 'c' :
					neuronCountMutation(m->minInputCount, m->minOutputCount,m->neuronCountProb, m->neuronCountBias, neuronCount );
					break;

				case 't' : 
					targetMutation(m->targetLimit, m->targetCountProb, m->targetCountBias, m->retargetProb);
					break;

				case 'p' :
					potentialsMutation(m->potentialProb, m->potentialStrength);
					break;

				case 'h' :
					// removing threshold mutations, threshold should be constant
					// thresholdMutation(m->potentialProb, m->potentialStrength);
					break;
			}
		}
	}


//function to mutate neuron count, probability encodes the probability of occurance, and the bias encodes the 
//probability of removing v.s. adding a neuron. 0 guarantees removal, 1 guarantees addition.

void neuronCountMutation(brain * b, int minInputCount, int minOutputCount, float probability, float bias)
{
	// roll dice
	if (randFloat() < probability )
	{
		if (randFloat() < bias)
		{
			// if less, add a neuron
			neuronCount++;
			neurons.emplace_back();
			initializeNeuron(&(b->neurons[b->neuronCount-1]), b->neuronCount);
		}
		else if (b->neuronCount > 1 + minInputCount +  minOutputCount) 
		{
			// if greater than bias, remove a neuron
			neuronCount--;
			
			neurons.pop_back();

			for (neuron x : neurons) 
			{ 
				// this is an expensive O(n^2) mutation, so it's important to give it a low probability, but it ensures we will not have to worry about pre-existing activation patterns coming back from the dead when add a neuron with the index of a neuron we previously removed
				x.randomize_for(neuronCount, neuronCount);
			}
		}
	}
}


void targetMutation(int targetCountLimit, float targetCountProbability, float targetCountBias , float retargetProbability, int neuronCount)
{
	// iterate over every neuron
	for(neuron x : neurons)
	{
		int targetCount = x.targets.size();

		if(targetCount > 0)
		{
			// if there exists targets, either remove, delete, or retarget
			if (targetCountProbability > randFloat())
			{
				// remove or delete based on bias
				if(targetCountBias > randFloat()  && targetCount < targetCountLimit)
				{
					// emplace new
					x.targets.emplace_back( randRange(neuronCount), (randFloat()*2)-1 );
				}
				else 
				{
					// pick an element to pop back, and swap it with the end
					std::swap(x.targets[randRange(targetCount)], x.targets.back());
					// pop off the end
					x.targets.pop_back();
				}
			}

			// retargeting code
			if (retargetProbability > randFloat() && targetCount > 0)
			{
				x.targets[randRange(targetCount)].target = randRange(neuronCount);
			}

		}
		else if (targetCountProbability > randFloat())
		{
			// if no targets, try to add a new target
			x.targets.emplace_back( randRange(neuronCount), (randFloat()*2)-1 );
		}
	}
}

/*
   Mutate Activation Potentials

probability: 0-1
strength: 0-infinity

 */

void potentialsMutation(float probability, float strength)
{
	// iterate over every neuron
	for(neuron x : neurons)
	{
		int targetCount = x.targets.size();

		if(targetCount <= 0) return;
	
		int mutations = randRange(targetCount);
		// perform a random number of mutations
		for (int c = 0 ; c < mutations; c++)
		{
			//TODO add soft boundary
			if(randFloat() < probability)
			{
				x.targets[randRange(targetCount)].weight += ((randFloat() *2)-1)*strength;
			}
		}
	}
}



};


/*
       fff        tt                                     tt
      ff     cccc tt    nn nnn     pp pp   rr rr   oooo  tt     oooo
      ffff cc     tttt  nnn  nn    ppp  pp rrr  r oo  oo tttt  oo  oo
      ff   cc     tt    nn   nn    pppppp  rr     oo  oo tt    oo  oo
      ff    ccccc  tttt nn   nn    pp      rr      oooo   tttt  oooo
                                   pp
*/

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
