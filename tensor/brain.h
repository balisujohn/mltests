// Michael Ivanitskiy, Connor Puritz
// Math 463 Fall 2018 Final Project

// puts everything together

#ifndef BRAIN
#define BRAIN

#include <unordered_map>
#include <queue>
#include "nets.h"
#include "util/err_util.h"

using namespace std;

class brain
{
private:

// array for layers
graph layers [NUM_LAYERS];
// neurons with nonzero voltage
unordered_map < neuron_coord, neuron, coordHasher > active_neurons;
// edges that have been modified
unordered_map < coord_pair, edge_base, coordPairHasher > mod_edges;
unordered_map < neuron_coord, edge, coordHasher > add_edges;

public:

brain() {}

brain(vector < string > filenames)
{
	CHK_ERROR_FATAL(filenames.size() != NUM_LAYERS, "wrong number of filenames");
	
	for (uint8_t i = 0; i < NUM_LAYERS; i++)
	{
		layers[i] = graph( i, filenames[i] );
	}
}

// iterate single timestep
void step()
{
	// update time
	TIME_CURRENT++;
	// iterate over active_neurons
	auto iter = active_neurons.begin();

	queue < neuron_coord > to_erase;

	while (iter != active_neurons.end())
	{
		neuron & n = iter->second;
		// if there are any spikes at all
		if (!(n.spikes_in.empty()))
		{
			// try to see if there is a spike at the current timestep
			if (n.spikes_in.top().t <= TIME_CURRENT)
			{
				// if yes, try to fire the neuron
				fire(n);
			}
		}
		else
		{
			// if there are no spikes, test the time since last update
			if ( n.t <= TIME_CURRENT - 1 )
			{
				// if it has been long enough, mark the neuron for removal
				to_erase.push(n.c);
			}
		}
	}

	// wipe marked neurons
	// this is to avoid index invalidation of the hash map
	while (!to_erase.empty()) 
	{
		active_neurons.erase(to_erase.front());
		to_erase.pop();
	}
}


// manually fire a neuron (such as an input neuron)
void fire_manual(neuron_coord & c)
{
	spike elt = spike();

	// find if neuron has been activated
	auto iter_n = active_neurons.find(c);

	if (iter_n == active_neurons.end())
	{
		// if found, add to that neuron
		iter_n->second.add_spike(elt);
	}
	else
	{
		// if not, create a new neuron and add this spike to it
		active_neurons.emplace(c, neuron(c));
		iter_n = active_neurons.find(c);
		iter_n->second.add_spike(elt);
	}
}

// test if a neuron with incoming spikes should fire
void fire(neuron & n)
{
	// if the neuron should fire at this timestep
	if (n.try_fire())
	{
		fire_all_adj(n, 0);
	}
}

// recursive function to fire all neurons adjacent to an input neuron "n"
void fire_all_adj(neuron & n, uint8_t layer)
{
	graph & graph_testing = layers[layer];
	neuron_coord coord;
	// for every adjacent neuron in the layer
	// 			   	   graph	adjlst   entry
	// 			   layers[layer].data[ n.c[layer] ]
	for ( uint8_t i = 0; i < graph_testing.size; i++ )
	{
		// access graph_testing 's data at n.c[layer] (the coordinate in the layer)
		// this tells us if the neuron with identical coordinates, but c[layer] set to "i"
		// is connected to our neuron n

		// if nonzero wgt
		if ( !zero_f(graph_testing.data[coord[layer]][i].wgt) )
		{
			push_spike_thru_edge(coord_pair(coord, coord.nrn_crd_replace(layer, i)), layer);
		}
	}
	
	
	if ( layer < NUM_LAYERS - 1 )
	{
		// if not at bottom layer, recurse
		fire_all_adj(n, layer + 1);
	}
}

inline void push_spike_thru_edge(coord_pair p, uint8_t L)
{
	auto iter_e = mod_edges.find(p);

	spike elt = spike();

	// check if edge has been modified
	if ( iter_e == mod_edges.end() )
	{
		// if not modified, use actual val
		// access graph at correct layer, 
		edge_base & e = layers[ L ].data[ p.in[ L ] ][ p.out[ L ] ];
		elt = spike(e.wgt, e.delay);
	}
	else
	{
		// if modified, use whatever was found
		edge_base & e = iter_e->second;
		elt = spike(e.wgt, e.delay);
	}

	// find if neuron has been activated
	auto iter_n = active_neurons.find(p.out);

	if (iter_n == active_neurons.end())
	{
		// if found, add to that neuron
		iter_n->second.add_spike(elt);
	}
	else
	{
		// if not, create a new neuron and add this spike to it
		active_neurons.emplace(p.out, neuron(p.out));
		iter_n = active_neurons.find(p.out);
		iter_n->second.add_spike(elt);
	}
}


};

#endif