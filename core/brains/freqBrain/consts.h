// John Balis, Michael Ivanitskiy 2019
// for support email:
// balisujohn@gmail.com 
// mivanits@umich.edu

#ifndef CONSTS
#define CONSTS

#include <cstdint>
#include <queue>
#include <vector>
#include <math.h>

using namespace std;

// these values should be set by a separate program before compile time
// using constant values improves speed significantly

// consts

// number of layers limited to 255
const uint8_t NUM_LAYERS = 4;

// number of nodes in any layer limited to 255
// network can thus have up to 255^255 or ~4.653e613 neurons
// 5 layers -> up to ~1.078 trillion (255^5) neurons
uint8_t LAYERS_SIZE [NUM_LAYERS] = { 5, 5, 5, 5 };

// input/output size is up to 65535, this can be changed relatively easily
uint16_t SIZE_INPUT = 5;
uint16_t SIZE_OUTPUT = 5;

// weight type
typedef float weight;
// voltage type
typedef float voltage;
// timestamp type
typedef uint16_t time;

time TIME_CURRENT = 0;

// resting voltage
const voltage V_REST = 0.0;
// threshold voltage to fire neuron
const voltage V_THRESHOLD = 100.0;
// amplitude of spikes, if threshold crossed
const voltage V_SPIKEAMP = 1000.0;
// voltage the next timestep after firing
const voltage V_RECOVERY = -30.0;
// percentage of voltage remaining after every timestep, if not fired
const voltage V_DECAY = 0.1;

// margin for comparing floats
const float EPSILON = 0.1;

// code for comparing two floats
inline bool compf(float a, float b)
{
    return fabs(a - b) <= EPSILON;
}

inline bool zero_f(float a)
{
	return fabs(a) <= EPSILON;
}



// custom type of "neuron_coord" as a size_t array of length NUM_LAYERS
struct neuron_coord
{
	neuron_coord() {}

	neuron_coord(uint8_t * in_data) 
	{
		for (uint8_t L = 0; L < NUM_LAYERS; L++)
		{
			data[L] = in_data[L];
		}
	}
	neuron_coord(neuron_coord * input)
	{
		for (uint8_t L = 0; L < NUM_LAYERS; L++)
		{
			data[L] = input->data[L];
		}
	}

	uint8_t data [NUM_LAYERS];

	inline uint8_t operator [] (uint8_t L)
	{
		return data[L];
	}

	// TODO: optimize this
	inline neuron_coord nrn_crd_replace(uint8_t layer, uint8_t value)
	{
		neuron_coord c(this);
		c.data[layer] = value;
		return c;
	}
};

struct coord_pair
{
	neuron_coord in;
	neuron_coord out;

	coord_pair(neuron_coord & a, neuron_coord & b) : in(a), out (b) {}
};

struct coordHasher
{
	coordHasher() {}

	size_t operator()(const neuron_coord & c) const
	{
		size_t out = 0;
		for (uint8_t i = 0; i < NUM_LAYERS; i++)
		{
			(out ^ (hash<uint8_t>()(c.data[i]) << 1)) >> 1;
			out = hash<size_t>()(out);
		}

		return out;
	}
};

struct coordPairHasher
{
	coordHasher hash_crd = coordHasher();

	size_t operator()(const coord_pair & p) const
	{
		return (hash_crd(p.in) ^ hash_crd(p.out));
	}
};


// floating point variable controlling the proportion of native edges that should be erased
// when their hash is taken
float edges_culled = 0.8;


#endif