// Michael Ivanitskiy, Connor Puritz
// Math 463 Fall 2018 Final Project

// file with edge class stuff

#ifndef EDGE
#define EDGE

#include "neuron.h"
#include "input/consts_template.h"

using namespace std;

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