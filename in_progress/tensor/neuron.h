// Michael Ivanitskiy, Connor Puritz
// Math 463 Fall 2018 Final Project

// file with neuron class stuff

#ifndef NEURON
#define NEURON

#include <limits>

#include "input/consts_template.h"

using namespace std;

class neuron
{
public:
// stores time voltages hit, voltage, and coordinate
neuron_coord c;
spikeTrain spikes_in;
voltage v;
time t;

neuron( neuron_coord in_c ) : v(V_REST), t(TIME_CURRENT) {}


// FIXME: use heapify for spike train vector
// FIXME: optimize by reading several before calling heapify again?
bool try_fire()
{	
	// if the time is too far in the past, reset voltage to rest value
	if (t + 1 < TIME_CURRENT) v = V_REST;
	t = TIME_CURRENT;

	// read until current time
	while (spikes_in.top().t <= TIME_CURRENT)
	{
		// updates only voltage at current time
		v += spikes_in.top().t;
	}

	// test if it fired
	if (v > V_THRESHOLD)
	{
		// set voltage next step to the recovery voltage after firing
		v = V_RECOVERY;
		return true;
	}
	else
	{
		// otherwise, the voltage to the next timestep should decay
		v *= V_DECAY;
		return false;
	}
}

// add_spike()
inline void add_spike(spike & input)
{
	spikes_in.push(input);
}

};


#endif