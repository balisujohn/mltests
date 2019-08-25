// Michael Ivanitskiy, Connor Puritz
// Math 463 Fall 2018 Final Project

#include <iostream>
#include <string>
#include <vector>

#include "brain.h"

using namespace std;

int main()
{
	// initialize
	vector < string > filenames (NUM_LAYERS, "input/basic5n.tsv");
	brain testbrain (filenames);

	// spike some neuron
	uint8_t arr [NUM_LAYERS] = {2,3,4,0};
	testbrain.fire_manual(neuron_coord(arr));
	arr[0] = 1; arr[3] = 3;
	testbrain.fire_manual(neuron_coord(arr));
	arr[1] = 0; arr[2] = 1;
	testbrain.fire_manual(neuron_coord(arr));

	// loop
	while (true)
	{
		testbrain.step();
	}

	return 0;
}

