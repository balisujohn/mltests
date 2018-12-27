from random import uniform, randrange
import copy
import math
import utils
import gym



class Neuron:
	
	def __init__(self):
		self.activation_potential = uniform(0,1)
		self.target_count = 0
		self.targets = []
		self.potential_weights = []
		self.fired = 0
		self.activation_potential = 0
		self.excitation = 0




class Brain:

	def __init__(self, neuron_count):
		self.neuron_count = neuron_count
		self.neurons = []
		for i in range(neuron_count):			
			self.neurons.append(Neuron())
	
	def print_brain(self): # needs testing
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
			elif self.neuron_count > 1 + min_input_count + min_output_count:
				self.neuron_count -= 1
				del self.neurons[self.neuron_count]
				for neuron in self.neurons:
					for index, target in enumerate(neuron.targets):
						if target >= self.neuron_count:
							neuron.targets[index] = randrange(0,self.neuron_count)


	def target_mutation(self, max_targets, target_count_probability, target_count_bias, retarget_probability):

		for i, neuron in enumerate(self.neurons):
			if  target_count_probability > uniform(0,1):
				if target_count_bias > uniform(0,1) :
					if neuron.target_count < max_targets:
						neuron.target_count += 1
						neuron.targets.append(randrange(0,self.neuron_count))
						neuron.potential_weights.append((uniform(0,1)*2)-1)
				else:
					if neuron.target_count > 0:
						neuron.target_count -= 1
						del neuron.targets[neuron.target_count]
						del neuron.potential_weights[neuron.target_count]


				if retarget_probability > uniform(0,1) and neuron.target_count > 0:
					neuron.targets[randrange(0,neuron.target_count)] = randrange(self.neuron_count)

					
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
		index1 = randrange(0, self.neuron_count -1) + 1 
		index2 = randrange(0, self.neuron_count -1) + 1 
		while index2 == index1:
			index2 = randrange(0, self.neuron_count -1) + 1 
		temp = self.neurons[index1]
		self.neurons[index1] = self.neurons[index2]
		self.neurons[index2] = temp

	
	def default_mutation(self, min_input_count, min_output_count):
		self.neuron_swap_mutation(.1)
		self.neuron_count_mutation(min_input_count, min_output_count, .125, .5)
		self.target_mutation(5,.25,.5,.25)
		self.potential_weights_mutation(1,.25)
		self.threshold_mutation(1,.5)

	
	def input(self, inputs):
		self.neurons[0].excitation = self.neurons[0].activation_potential + 1
		for i in range(1, len(inputs) + 1 ):
			self.neurons[i].excitation = inputs[i-1] * (self.neurons[i].activation_potential + 1)
			
		
	def advance(self, inputs, output_length):

		assert not (self.neuron_count < 1 + len(inputs) + output_length)
		self.input(inputs)
		sums  = [0] * self.neuron_count

		for i in range(self.neuron_count):
			self.neurons[i].fired = 0
			if self.hyperbolic_tangent(self.neurons[i].excitation) > self.neurons[i].activation_potential:
				for c in range (self.neurons[i].target_count):
					
					assert(self.neurons[i].targets[c] < self.neuron_count)
					sums[self.neurons[i].targets[c]] += self.neurons[i].potential_weights[c]
				self.neurons[i].fired = 1
				self.neurons[i].excitation = 0.0
			self.neurons[i].excitation = self.neurons[i].excitation/2.0
		
		for i in range(self.neuron_count):
			self.neurons[i].excitation += sums[i]
		assert(len(inputs) + output_length + 1 <= self.neuron_count )
		start = len(inputs) + 1
		outputs = []
		for i in range(output_length):
			outputs.append(self.neurons[start + i].fired)
		
		return outputs
	

