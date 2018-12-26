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
		#print("NEURON COUNT: " + str(self.neuron_count)) 

		#print("NEURONS LENGTH: " + str(len(self.neurons))) 
		#assert(self.neuron_count == len(self.neurons))
		#for neuron in self.neurons:
		#	for target in neuron.targets:
		#		print('TARGET: ' + str(target))
		#		print("NEURON COUNT: " + str(self.neuron_count)) 
		#		assert(target < self.neuron_count)
		pass
		

	def neuron_count_mutation(self, min_input_count, min_output_count, probability, bias):
		self.verify_network_consistency()
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
		self.verify_network_consistency()

	def target_mutation(self, max_targets, target_count_probability, target_count_bias, retarget_probability):
		self.verify_network_consistency()		
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
		self.verify_network_consistency()
					
	def potential_weights_mutation(self, probability, strength):
		self.verify_network_consistency()
		for neuron in self.neurons:
			if neuron.target_count > 0:
				mutations = randrange(0, neuron.target_count)
				for i in range(mutations):
					if uniform(0,1) < probability:
						neuron.potential_weights[randrange(0,neuron.target_count)] += ((uniform(0,1) *2)-1)*strength
		self.verify_network_consistency()
	def threshold_mutation(self, probability, strength):
		self.verify_network_consistency()		
		for neuron in self.neurons:
			if uniform(0,1) < probability:
				neuron.activation_potential += ((uniform(0,1) *2)-1)*strength
		self.verify_network_consistency()

	def neuron_swap_mutation(self, probability):
		self.verify_network_consistency()
		index1 = randrange(0, self.neuron_count -1) + 1 
		index2 = randrange(0, self.neuron_count -1) + 1 
		while index2 == index1:
			index2 = randrange(0, self.neuron_count -1) + 1 
		temp = self.neurons[index1]
		self.neurons[index1] = self.neurons[index2]
		self.neurons[index2] = temp
		self.verify_network_consistency()
	
	def default_mutation(self, min_input_count, min_output_count):
		self.verify_network_consistency()		
		self.neuron_swap_mutation(.1)
		self.neuron_count_mutation(min_input_count, min_output_count, .125, .5)
		self.target_mutation(5,.25,.5,.25)
		self.potential_weights_mutation(1,.1)
		self.threshold_mutation(1,.1)
		self.verify_network_consistency()
	
	def input(self, inputs):
		self.neurons[0].excitation = self.neurons[0].activation_potential + 1
		for i in range(1, len(inputs) + 1 ):
			self.neurons[i].excitation = inputs[i-1] * (self.neurons[i].activation_potential + 1)
			
		
	def advance(self, inputs, output_length):
		#print ('NEURON COUNT: ' + str(self.neuron_count) + '\nINPUT LENGTH: ' + str(len(inputs)))
		assert not (self.neuron_count < 1 + len(inputs) + output_length)
		self.input(inputs)
		sums  = [0] * self.neuron_count
		#print(len(sums))
		for i in range(self.neuron_count):
			self.neurons[i].fired = 0
			if self.hyperbolic_tangent(self.neurons[i].excitation) > self.neurons[i].activation_potential:
				for c in range (self.neurons[i].target_count):
					#print(len(self.neurons[i].targets))
					#print(len(self.neurons[i].potential_weights))
					#print(self.neurons[i].targets[c])
					#print('TARGET COUNT: ' + str(self.neurons[i].target_count))
					#print('TARGET INDEX: ' + str(c))
					#print('TARGET: ' + str(self.neurons[i].targets[c]))
					#print('SUMS: ' + str(len(sums)))
					assert(self.neurons[i].targets[c] < self.neuron_count)
					sums[self.neurons[i].targets[c]] += self.neurons[i].potential_weights[c]
					#sums[1] += self.neurons[i].potential_weights[c]
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

		
	def evaluate_xor_performance(self):
		test_instance_1 = copy.deepcopy(self)		
		test_instance_2 = copy.deepcopy(self)
		test_instance_3 = copy.deepcopy(self)
		test_instance_4 = copy.deepcopy(self)

		[input_1,input_2,input_3,input_4] = [[0,0],[0,1],[1,0],[1,1]]

		[goal_1,goal_2,goal_3,goal_4] = [1,0,0,1]




		output_1 = 0
		output_2 = 0
		output_3 = 0
		output_4 = 0

		for i in range(5):
			output_1 = test_instance_1.advance(input_1,1) 
			output_2 = test_instance_2.advance(input_2,1)
			output_3 = test_instance_3.advance(input_3,1)
			output_4 = test_instance_4.advance(input_4,1)




	#	print(output_1)
	#	print(str(goal_1) + "\n")




		score = 0
		if output_1[0] == goal_1:
			score += 25
		if output_2[0] == goal_2:
			score += 25
		if output_3[0] == goal_3:
			score += 25
		if output_4[0] == goal_4:
			score += 25


		#if score == 100:
	#		print([input_1,input_2,input_3,input_4])
	#		print([goal_1,goal_2,goal_3,goal_4])
		return score

	def analyze(self, input_count, output_count):
		while True:
			test_instance = copy.deepcopy(self)
			
			inputs = str(raw_input("PLEASE ENTER " + str(input_count) + " INPUTS:\n"))
			inputs = [int(char) for char in inputs]
			#print (inputs)
			time_slices = int(input("PLEASE ENTER DESIRED NUMBER OF TIME SLICES:\n"))
			outputs = []
			for i in range(time_slices):
				outputs = self.advance(inputs, output_count)
			print ("OUTPUTS: " + str(outputs))
		



def learn_xor():

	best_brain = Brain(4)
	best_brain.verify_network_consistency()
	best_score = 0
	
	counter = 0 	
	average = 0	
	
	while best_score < 100:
		counter += 1
		score = 0
		
		mutant = copy.deepcopy(best_brain) 
		#mutant.print_brain()
		#best_brain.print_brain()	
		best_brain.verify_network_consistency()	
		mutant.verify_network_consistency()
		mutant.default_mutation(2,1)
		mutant.verify_network_consistency()
		test_instance = copy.deepcopy(mutant)
		test_instance.verify_network_consistency()
		score = test_instance.evaluate_xor_performance()
		average += score
		if ((counter % 100) == 0):
			print ('LAST 100 AVERAGE: ' + str(average/100))
			average = 0
		if score > best_score:
			print('NEW BEST SCORE: ' + str(score))
		#	test_instance.print_brain()
			best_score = score
			mutant.verify_network_consistency()
			best_brain = copy.deepcopy(mutant)
			best_brain.verify_network_consistency()
	

	return best_brain




def evaluate_space_invaders_performance(brain):

	top_indices = [87, 79, 80, 77, 112, 1, 8, 72, 6, 28, 3, 110, 82, 85, 78, 9, 81, 90, 106, 74]
	
	env = gym.make('SpaceInvaders-ram-v0')
	observations = env.reset()
	score = 0
	while 1:
		score += 1
		#env.render()
		#print(observation)

		output = [0] * 3
		inputs = utils.extract_observations(top_indices, observations)
		#print(inputs)
		#print(len(inputs))
		assert(len(inputs) == 160)

		for i in range(5):
			output = brain.advance(inputs, 3)
		#print(output)
		#print(output)
		action = min(utils.binary_array_to_decimal(output), 5)
		#print(action)

		observations,reward,done,info = env.step(action)
		if done:
			return score
		
		


	#feedback loop with microworld




def learn_space_invaders():

	best_brain = Brain(164)
	best_brain.verify_network_consistency()
	best_score = 0
	
	counter = 0 	
	average = 0	
	
	while best_score < 1000:
		counter += 1
		score = 0
		
		mutant = copy.deepcopy(best_brain) 
		#mutant.print_brain()
		#best_brain.print_brain()	
		#best_brain.verify_network_consistency()	
		#mutant.verify_network_consistency()
		mutant.default_mutation(160,3)
		#mutant.verify_network_consistency()
		test_instance = copy.deepcopy(mutant)
		#test_instance.verify_network_consistency()
		score = evaluate_space_invaders_performance(test_instance)
		average += score
		if ((counter % 100) == 0):
			print ('LAST 100 AVERAGE: ' + str(average/100))
			average = 0
		if score > best_score:
			print('NEW BEST SCORE: ' + str(score))
		#	test_instance.print_brain()
			best_score = score
			#mutant.verify_network_consistency()
			best_brain = copy.deepcopy(mutant)
			#best_brain.verify_network_consistency()
	

	return best_brain

		
				
learn_space_invaders()
#evaluate_space_invaders_performance(Brain(164))
				

