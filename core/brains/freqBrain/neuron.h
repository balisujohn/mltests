// John Balis, Michael Ivanitskiy 2019
// for support email:
// balisujohn@gmail.com 
// mivanits@umich.edu

// file with neuron class stuff

#ifndef NEURON
#define NEURON

#include <limits>

#include "consts.h"

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

	// experimental:
	time term;
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
vector < pulse > waveform;
time t;

neuron( neuron_coord in_c ) : t(TIME_CURRENT) {}



};


/*
   ####       ##  #######     ##    ## ######## ##     ## ########   #######  ##    ##
    ##       ##  ##     ##    ###   ## ##       ##     ## ##     ## ##     ## ###   ##
    ##      ##   ##     ##    ####  ## ##       ##     ## ##     ## ##     ## ####  ##
    ##     ##    ##     ##    ## ## ## ######   ##     ## ########  ##     ## ## ## ##
    ##    ##     ##     ##    ##  #### ##       ##     ## ##   ##   ##     ## ##  ####
    ##   ##      ##     ##    ##   ### ##       ##     ## ##    ##  ##     ## ##   ###
   #### ##        #######     ##    ## ########  #######  ##     ##  #######  ##    ##
*/





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