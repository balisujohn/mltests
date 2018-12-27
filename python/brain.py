from random import uniform, randrange
from enum import Enum
import copy
import math
import utils
import json
import gym

class Brain_flags(Enum): ## dont change the existing ones without updating in mutation function
	NEURON_HIDDEN = 1
	NEURON_SENSORY = 2
	NEURON_ACTUATING = 3
	SENSOR_BIT = 4
	SENSOR_LINEAR_THRESHOLD = 5


class Neuron:
	
	def __init__(self):
		self.activation_potential = uniform(0,1)
		self.target_count = 0
		self.targets = []
		self.potential_weights = []
		self.fired = 0
		self.excitation = 0
		
		self.type = Brain_flags.NEURON_HIDDEN
		self.sensor_type = Brain_flags.SENSOR_BIT # not initalized to consistent vales(not used until neuron set to sensory or actuating)
		self.external_index = 0
		self.external_thresh = 0
		self.external_bit = 0



class Brain:

	def __init__(self, neuron_count):
		self.neuron_count = neuron_count
		self.neurons = []
		for i in range(neuron_count):			
			self.neurons.append(Neuron())
	
	def print_brain(self):
		print("ACTIVATION: ") 
		for neuron in self.neurons:
			print (str(neuron.fired)),
		print('')			
		for index, neuron in enumerate(self.neurons):
			print ("NEURON {index}".format(index = index))
			for i in range(neuron.target_count):
				print ("TARGET: {target}, WEIGHT: {weight}".format(target = neuron.targets[i],weight = neuron.potential_weights[i]))
		print('NEURON COUNT RECORD: ' +  str(self.neuron_count))
		print('NEURON COUNT: ' + str(len(self.neurons)))
			


	
	def sigmoid(self, x):
		 return 1 / (1 + math.exp(float( -x)))


	def hyperbolic_tangent(self, x):
		return 2*self.sigmoid(2*x)-1

	def verify_network_consistency(self):
		print("NEURON COUNT: " + str(self.neuron_count)) 

		print("NEURONS LENGTH: " + str(len(self.neurons))) 
		assert(self.neuron_count == len(self.neurons))
		for neuron in self.neurons:
			for target in neuron.targets:
				print('TARGET: ' + str(target))
				print("NEURON COUNT: " + str(self.neuron_count)) 
				assert(target < self.neuron_count)
		pass
		

	def neuron_count_mutation(self, min_input_count, min_output_count, probability, bias):

		if uniform(0,1) < probability:		
			if uniform(0,1) < bias:
				self.neurons.append(Neuron())	#needs neuron init function
				self.neuron_count  += 1
			elif self.neuron_count > 1:# + min_input_count + min_output_count:
				self.neuron_count -= 1
				del self.neurons[self.neuron_count]
				for neuron in self.neurons:
					for index, target in enumerate(neuron.targets):
						if target >= self.neuron_count:
							neuron.targets[index] = randrange(0,self.neuron_count)


	def target_mutation(self, max_targets, target_count_probability, target_count_bias, retarget_probability):
		if self.neuron_count > 1:
			for i, neuron in enumerate(self.neurons):
				if  target_count_probability > uniform(0,1):
					if target_count_bias > uniform(0,1) :
						if neuron.target_count < max_targets:
							neuron.target_count += 1
							new_target = randrange(0,self.neuron_count)
							while new_target == i:
								new_target = randrange(0,self.neuron_count)
							neuron.targets.append(new_target)
							neuron.potential_weights.append((uniform(0,1)*2)-1)
					else:
						if neuron.target_count > 0:
							neuron.target_count -= 1
							del neuron.targets[neuron.target_count]
							del neuron.potential_weights[neuron.target_count]


					if retarget_probability > uniform(0,1) and neuron.target_count > 0:
						neuron.targets[randrange(0,neuron.target_count)] = randrange(self.neuron_count)

	


	# note that the probabilities must add up to one or less here
	def type_mutation(self, input_count, output_count, sensory_mutation_prob, actuating_mutation_prob, hidden_mutation_prob):
		for neuron in self.neurons:
			selection = uniform(0,1)			
			if selection < sensory_mutation_prob:
				neuron.type = Brain_flags.NEURON_SENSORY
				neuron.sensor_type = Brain_flags(randrange(4,6))
				neuron.external_index = randrange(input_count)
				neuron.external_thresh = randrange(256)
				neuron.external_bit = randrange(8)
	
			elif selection < sensory_mutation_prob + actuating_mutation_prob:
				neuron.type = Brain_flags.NEURON_ACTUATING
				neuron.external_index = randrange(output_count)
		
		
			elif selection < sensory_mutation_prob + actuating_mutation_prob + hidden_mutation_prob:
				neuron.type = Brain_flags.NEURON_HIDDEN
			
			

					
	def potential_weights_mutation(self, probability, strength):

		for neuron in self.neurons:
			if neuron.target_count > 0:
				mutations = randrange(0, neuron.target_count)
				for i in range(mutations):
					if uniform(0,1) < probability:
						neuron.potential_weights[randrange(0,neuron.target_count)] += ((uniform(0,1) *2)-1)*strength

	def threshold_mutation(self, probability, strength):

		for neuron in self.neurons:
			if uniform(0,1) < probability:
				neuron.activation_potential += ((uniform(0,1) *2)-1)*strength


	def neuron_swap_mutation(self, probability):
		if self.neuron_count > 1:
			index1 = randrange(0, self.neuron_count)  
			index2 = randrange(0, self.neuron_count)  
			while index2 == index1:
				index2 = randrange(0, self.neuron_count) 
			temp = self.neurons[index1]
			self.neurons[index1] = self.neurons[index2]
			self.neurons[index2] = temp
			assert(len(self.neurons) == self.neuron_count)
			for index, neuron in enumerate(self.neurons):
				for i in range(neuron.target_count):
					while neuron.targets[i] == index:
						neuron.targets[i] = randrange(self.neuron_count) 

	
	def default_mutation(self, input_count, output_count):
		self.neuron_swap_mutation(.1)
		self.neuron_count_mutation(input_count, output_count, .125, .5)
		self.target_mutation(5,.25,.5,.25)
		self.potential_weights_mutation(1,.25)
		self.threshold_mutation(1,.5)
		self.type_mutation(input_count, output_count,.1,.1,.1)

	



	def input(self, inputs):
		self.neurons[0].excitation = self.neurons[0].activation_potential + 1  # activating the bias neuron



		for i in range(1, len(inputs) + 1 ):
			self.neurons[i].excitation = inputs[i-1] * (self.neurons[i].activation_potential + 1)
			
		
	def advance(self, inputs, output_length):

		#assert not (self.neuron_count < 1 + len(inputs) + output_length)
		#self.input(inputs)
		sums  = [0] * self.neuron_count
		outputs = [0] * output_length

		for i,neuron in enumerate(self.neurons):

			if neuron.fired:
				neuron.fired = 0
				if neuron.type == Brain_flags.NEURON_ACTUATING:
					outputs[neuron.external_index] = 1
	

			if neuron.type == Brain_flags.NEURON_SENSORY:
				observation = inputs[neuron.external_index]
				if neuron.sensor_type == Brain_flags.SENSOR_BIT:
					if (observation >> neuron.external_bit) & 1:	
						neuron.excitation = neuron.activation_potential + 1 
				elif self.neurons[i].sensor_type == Brain_flags.SENSOR_LINEAR_THRESHOLD:
					if observation > neuron.external_thresh:
						neuron.excitation = neuron.activation_potential + 1 


			elif self.hyperbolic_tangent(self.neurons[i].excitation) > self.neurons[i].activation_potential:
				for c in range (self.neurons[i].target_count):
					
					assert(self.neurons[i].targets[c] < self.neuron_count)
					sums[self.neurons[i].targets[c]] += self.neurons[i].potential_weights[c]
				self.neurons[i].fired = 1
				self.neurons[i].excitation = 0.0
			self.neurons[i].excitation = self.neurons[i].excitation/2.0
		
		for i in range(self.neuron_count):
			self.neurons[i].excitation += sums[i]
		#assert(len(inputs) + output_length + 1 <= self.neuron_count )
		#start = len(inputs) + 1
		#outputs = [0]
		#for i in range(output_length):
		#	outputs.append(self.neurons[start + i].fired)
		
		return outputs
	

def print_brain_to_file(brain):
	data = {}
	data['neuronCount'] = len(brain.neurons)
	data['neurons'] = []
	for neuron in brain.neurons:
		neuron_dict = {}
		neuron_dict['targets'] = neuron.targets
		neuron_dict['weights'] = neuron.potential_weights
		neuron_dict['thresh'] =  neuron.activation_potential
		neuron_dict['targetCount'] = neuron.target_count

		neuron_dict['neuronType'] = neuron.type.name
		neuron_dict['sensorType'] = neuron.sensor_type.name



		neuron_dict['externalIndex'] = neuron.external_index
		neuron_dict['externalThreshold'] = neuron.external_thresh
		neuron_dict['externalBit'] = neuron.external_bit
		data['neurons'].append(neuron_dict)

	output = json.dumps(data, indent = 4)
	output_file = open('log.txt', 'w')
	output_file.write(output)
	output_file.close()
	




#def load_brain_from_file():
	



