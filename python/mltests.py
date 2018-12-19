import random



class Neuron:
	target_count = 0
	targets = []
	potential_weights = []
	fired = 0
	activation_potential = 0
	excitation = 0
	def __init__(self):
		self.activation_potential = random.uniform(0,1)
	




class Brain:
	neuron_count = 0
	neurons = []
	def __init__(self, neuron_count):
		self.neuron_count = neuron_count
		for i in range(neuron_count):
			self.neurons.append(Neuron())
	
	def print_brain(self): # needs testing
		print("ACTIVATION: ") 
		for neuron in self.neurons:
			print (str(neuron.fired)),
		for index, neuron in enumerate(self.neurons):
			print ("NEURON {index}".format(index = index))
			for i in range(neuron.target_count):
				print ("TARGET: {target}, WEIGHT: {weight}".format(target = neuron.targets.get(i),weight = neuron.potential_weights.get(i)))
			
			



b = Brain(3)
b.print_brain()
