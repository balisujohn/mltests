// John Balis, Michael Ivanitskiy 2019
// for support email:
// balisujohn@gmail.com 
// mivanits@umich.edu

// file with neuron class stuff

#ifndef NEURON
#define NEURON

#include <limits>

#include "input/consts_template.h"

using namespace std;

/*
   ########  ##     ## ##        ######  ########
   ##     ## ##     ## ##       ##    ## ##
   ##     ## ##     ## ##       ##       ##
   ########  ##     ## ##        ######  ######
   ##        ##     ## ##             ## ##
   ##        ##     ## ##       ##    ## ##
   ##         #######  ########  ######  ########
*/

// chain of pulses, a set (best data structure TBD) of these is stored in every neuron to store the firing pattern
// this implementation treats time as discrete, for niceness
class pulse
{
	time period;
	time phase_shift;
	voltage amplitude;
};



/*
   ##    ## ######## ##     ## ########   #######  ##    ##
   ###   ## ##       ##     ## ##     ## ##     ## ###   ##
   ####  ## ##       ##     ## ##     ## ##     ## ####  ##
   ## ## ## ######   ##     ## ########  ##     ## ## ## ##
   ##  #### ##       ##     ## ##   ##   ##     ## ##  ####
   ##   ### ##       ##     ## ##    ##  ##     ## ##   ###
   ##    ## ########  #######  ##     ##  #######  ##    ##
*/

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

/*
   ######## ########   ######   ########  ######
   ##       ##     ## ##    ##  ##       ##    ##
   ##       ##     ## ##        ##       ##
   ######   ##     ## ##   #### ######    ######
   ##       ##     ## ##    ##  ##             ##
   ##       ##     ## ##    ##  ##       ##    ##
   ######## ########   ######   ########  ######
*/

// modified edge weight
struct edge_base
{
	edge_base() : wgt(0) {}

	edge_base(weight in_wgt, float in_delay = 0)
		: wgt(in_wgt), delay(in_delay) {}

	weight wgt;
	float delay;
};

// input edge
struct edge_in : public edge_base
{
	uint8_t in;
	neuron_coord out;
};

// output edge
struct edge_out : public edge_base
{
	neuron_coord in;
	uint8_t out;
};

struct edge : public edge_base
{
	neuron_coord in;
	neuron_coord out;
};

struct edge_m : public edge_base
{
	neuron_coord in;
};


#endif