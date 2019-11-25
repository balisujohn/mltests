import sys
sys.path.insert(0,".")
sys.path.insert(0,"..")

#John Balis 2019
#for support email balisujohn@gmail.com

from random import uniform, randrange
from enum import Enum
import copy
import math
import utils
import json
import numpy
import visualization 


######## ##    ## ##     ## ##     ##
##       ###   ## ##     ## ###   ###
##       ####  ## ##     ## #### ####
######   ## ## ## ##     ## ## ### ##
##       ##  #### ##     ## ##     ##
##       ##   ### ##     ## ##     ##
######## ##    ##  #######  ##     ##

#ENUM for neuron types

class Brain_flags(Enum): ## dont change the existing ones without updating in mutation function
	NEURON_HIDDEN = 1
	NEURON_SENSORY = 2
	NEURON_ACTUATING = 3
	SENSOR_BIT = 4
	SENSOR_LINEAR_THRESHOLD_UP = 5
	SENSOR_LINEAR_THRESHOLD_DOWN = 6
	SENSOR_BINARY = 7



##     ## ##     ## ########    ########  ########  ##     ##
###   ### ##     ##    ##       ##     ## ##     ## ###   ###
#### #### ##     ##    ##       ##     ## ##     ## #### ####
## ### ## ##     ##    ##       ########  ########  ## ### ##
##     ## ##     ##    ##       ##        ##   ##   ##     ##
##     ## ##     ##    ##       ##        ##    ##  ##     ##
##     ##  #######     ##       ##        ##     ## ##     ##


#Global mutation parameters, here set to defaults

class Mutation_params():
	neuron_start_count = 1
	swap_prob = .1
	neuron_count_prob = .5
	neuron_count_bias = .5 
	target_limit = 5
	target_count_prob = .25
	target_count_bias = .5
	retarget_prob = .25
	potential_prob = .1
	potential_strength = .1
	threshold_prob = .1
	threshold_strength = .1
	reflex_pair_prob = .10
	input_count = 	10
	output_count = 10

	sensory_prob = .25
	actuating_prob = .25
	hidden_prob = .1

	mutation_cycles = 1
	upper_input_bounds = []
	lower_input_bounds = []



	def set_mutation_to_default_1(self): # most basic default setting, employing no experimental mutations
		self.neuron_start_count = 1
		self.swap_prob = .1
		self.neuron_count_prob = .5
		self.neuron_count_bias = .5
		self.target_limit = 5
		self.target_count_prob = .25
		self.target_count_bias = .5
		self.retarget_prob = .25
		self.potential_prob = .1
		self.potential_strength = .1
		self.threshold_prob = .1
		self.threshold_strength = .1
		self.reflex_pair_prob = 0
		self.input_count = 	10
		self.output_count = 10



		self.sensory_prob = .25
		self.actuating_prob = .25
		self.hidden_prob = .1

		self.correlator_prob = 0
		self.decorrelator_prob = 0
		self.generic_prob = 0


		self.mutation_cycles = 1
		self.upper_input_bounds = []
		self.lower_input_bounds = []


	def supress_mutation(self): #todo review for correctness
		self.swap_prob += (1-self.swap_prob)/2
		self.neuron_count_prob +=(1-self.neuron_count_prob)/2
		self.target_count_prob +=(1-self.target_count_prob)/2
		self.retarget_prob += (1-self.retarget_prob)/2
		self.potential_prob += (1-self.potential_prob)/2
		self.threshold_prob += (1-self.threshold_prob)/2
		self.sensory_prob += (1-self.sensory_prob)/2
		self.actuating_prob += (1-self.actuating_prob)/2
		self.hidden_prob += (1-self.hidden_prob)/2
	

	def amplify_mutation(self):
		self.swap_prob = self.swap_prob/2
		self.neuron_count_prob = self.neuron_count_prob/2
		self.target_count_prob =self.target_count_prob/2
		self.retarget_prob = self.retarget_prob/2
		self.potential_prob = self.potential_prob/2
		self.threshold_prob = self.threshold_prob/2
		self.sensory_prob= self.sensory_prob/2
		self.actuating_prob = self.actuating_prob/2
		self.hidden_prob = self.hidden_prob/2

	def set_to_default_low_intensity(self):
		self.swap_prob  = .05
		self.neuron_count_prob =.05
		self.target_count_prob=.05
		self.retarget_prob=.05
		self.potential_prob =.05
		self.threshold_prob =.05
		self.sensory_prob =.05
		self.actuating_prob =.05
		self.hidden_prob =.05
	
	

##    ## ######## ##     ## ########   #######  ##    ##
###   ## ##       ##     ## ##     ## ##     ## ###   ##
####  ## ##       ##     ## ##     ## ##     ## ####  ##
## ## ## ######   ##     ## ########  ##     ## ## ## ##
##  #### ##       ##     ## ##   ##   ##     ## ##  ####
##   ### ##       ##     ## ##    ##  ##     ## ##   ###
##    ## ########  #######  ##     ##  #######  ##    ##



class Neuron:
	
	def __init__(self):
		self.activation_potential = uniform(0,1)
		self.target_count = 0
		self.targets = []
		self.potential_weights = []
		self.fired = 0
		self.excitation = 0
		
		self.type = Brain_flags.NEURON_HIDDEN
		self.sensor_type = Brain_flags.SENSOR_BINARY # not initalized to consistent vales(not used until neuron set to sensory or actuating)
		self.external_index = 0
		self.external_thresh = 0
		self.external_bit = 0
		



########  ########     ###    #### ##    ##
##     ## ##     ##   ## ##    ##  ###   ##
##     ## ##     ##  ##   ##   ##  ####  ##
########  ########  ##     ##  ##  ## ## ##
##     ## ##   ##   #########  ##  ##  ####
##     ## ##    ##  ##     ##  ##  ##   ###
########  ##     ## ##     ## #### ##    ##


class Brain:



		#### ##    ## #### ########
		 ##  ###   ##  ##     ##
		 ##  ####  ##  ##     ##
		 ##  ## ## ##  ##     ##
		 ##  ##  ####  ##     ##
		 ##  ##   ###  ##     ##
		#### ##    ## ####    ##



	def __init__(self):
		self.neuron_count = Mutation_params.neuron_start_count
		self.neurons = []
		for i in range(self.neuron_count):			
			self.neurons.append(Neuron())
	
         ########  ########  #### ##    ## ########
         ##     ## ##     ##  ##  ###   ##    ##
         ##     ## ##     ##  ##  ####  ##    ##
         ########  ########   ##  ## ## ##    ##
         ##        ##   ##    ##  ##  ####    ##
         ##        ##    ##   ##  ##   ###    ##
         ##        ##     ## #### ##    ##    ##

	def print_brain(self):
		print("ACTIVATION: ") 
		for neuron in self.neurons:
			print (str(neuron.fired)),
		print('')			
		for index, neuron in enumerate(self.neurons):
			print ("NEURON {index}".format(index = index))
			for i in range(neuron.target_count):
				print ("TARGET: {target}, WEIGHT: {weight}".format(target = neuron.targets[i],weight = neuron.potential_weights[i]))
		print('NEURON COUNT RECORD: ' + str(self.neuron_count))
		print('NEURON COUNT: ' + str(len(self.neurons)))
			
	#def print_activation_record(self):
		#for index, neuron in enumerate(self.neurons):
		#	print("NEURON " + str(index) + ":")		
		#	neuron.print_activation_record()
		



            ###     ######  ######## ##     ## ##    ##
           ## ##   ##    ##    ##    ##     ## ###   ##
          ##   ##  ##          ##    ##     ## ####  ##
         ##     ## ##          ##    ##     ## ## ## ##
         ######### ##          ##     ##   ##  ##  ####
         ##     ## ##    ##    ##      ## ##   ##   ###
         ##     ##  ######     ##       ###    ##    ##
	
	def sigmoid(self, x):
		 return 1 / (1 + math.exp(float( -x)))


	def hyperbolic_tangent(self, x):
		return 2*self.sigmoid(2*x)-1

	def verify_network_consistency(self):
		#print("NEURON COUNT: " + str(self.neuron_count)) 

		#print("NEURONS LENGTH: " + str(len(self.neurons))) 
		assert(self.neuron_count == len(self.neurons))
		for i,neuron in enumerate(self.neurons):
			for target in neuron.targets:
		#		print('TARGET: ' + str(target))
		#		print("NEURON COUNT: " + str(self.neuron_count)) 
				assert(target < self.neuron_count)
				assert(target != i)
		pass
		

         ##     ## ##     ## ########    ###    ######## ########
         ###   ### ##     ##    ##      ## ##      ##    ##
         #### #### ##     ##    ##     ##   ##     ##    ##
         ## ### ## ##     ##    ##    ##     ##    ##    ######
         ##     ## ##     ##    ##    #########    ##    ##
         ##     ## ##     ##    ##    ##     ##    ##    ##
         ##     ##  #######     ##    ##     ##    ##    ########

	def neuron_count_mutation(self, min_input_count, min_output_count, probability, bias):

		if uniform(0,1) < probability:		
			if uniform(0,1) < bias:
				self.neurons.append(Neuron())	#needs neuron init function
				self.neuron_count += 1
			

			elif self.neuron_count > 1:# + min_input_count + min_output_count:
				self.neuron_count -= 1
				del self.neurons[self.neuron_count]
				
				if self.neuron_count > 1:
					for neuron_index, neuron in enumerate(self.neurons):
						for target_index, target in enumerate(neuron.targets):
							if target >= self.neuron_count:
								new_target = randrange(0,self.neuron_count)
								while new_target == neuron_index:
									new_target = randrange(0,self.neuron_count)
								neuron.targets[target_index] = new_target

				else: 
					self.neurons[0].targets = []
					self.neurons[0].target_count = 0
		#self.verify_network_consistency()
		


	def target_mutation(self, max_targets, target_count_probability, target_count_bias, retarget_probability):
		if self.neuron_count > 1:
			for i, neuron in enumerate(self.neurons):
				if target_count_probability > uniform(0,1):
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
						new_target = randrange(self.neuron_count)
						while new_target == i:
							new_target = randrange(self.neuron_count)
						neuron.targets[randrange(0,neuron.target_count)] = new_target



	# note that the probabilities must add up to one or less here #todo add automatic scaling
	def type_mutation(self, input_count, output_count, sensory_mutation_prob, actuating_mutation_prob, hidden_mutation_prob):
		for neuron in self.neurons:
			selection = uniform(0,1)			
			if selection < sensory_mutation_prob:
				neuron.type = Brain_flags.NEURON_SENSORY
				neuron.sensor_type = Brain_flags(randrange(5,8)) #sensor bit temporarily disabled
				neuron.external_index = randrange(input_count)
				neuron.external_thresh = uniform(Mutation_params.lower_input_bounds[neuron.external_index],Mutation_params.upper_input_bounds[neuron.external_index])
				#neuron.external_bit = randrange(8)
	
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
				neuron.activation_potential = max(0, neuron.activation_potential)


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
					if neuron.targets[i] == index1:
						neuron.targets[i] = index2
					elif neuron.targets[i] == index2:
						neuron.targets[i] = index1
			#self.verify_network_consistency()
	
	

	#reflex pair mutation
	#simple topologies often rely on simple input-output mappings. This mutation attempts to capitalize on this.

	def reflex_pair_mutation(self):
		input_count = Mutation_params().input_count
		output_count = Mutation_params().output_count

		if uniform(0,1) < Mutation_params().reflex_pair_prob:

			old_neuron_count = self.neuron_count
			sensor = Neuron()
			sensor.type = Brain_flags.NEURON_SENSORY
			sensor.sensor_type = Brain_flags(randrange(5,8))
			sensor.external_index = randrange(input_count)
			sensor.external_thresh = uniform(Mutation_params.lower_input_bounds[sensor.external_index],Mutation_params.upper_input_bounds[sensor.external_index])
			sensor.potential_weights.append(.23) #this horrible magic number is just a starting point for guaranteed activation
			sensor.targets.append(old_neuron_count+1)
			sensor.target_count+= 1		
			actuator = Neuron()
			actuator.type = Brain_flags.NEURON_ACTUATING
			actuator.external_index = randrange(output_count)
			actuator.activation_potential = .1
			self.neurons.append(sensor)
			self.neurons.append(actuator)
			self.neuron_count += 2





	def default_mutation(self, input_count, output_count):

		for i in range(Mutation_params().mutation_cycles):
			#self.verify_network_consistency()
			self.neuron_count_mutation(input_count, output_count, Mutation_params().neuron_count_prob,Mutation_params().neuron_count_bias)	
			#self.verify_network_consistency()
			self.neuron_swap_mutation(Mutation_params().swap_prob)
			#self.verify_network_consistency()
			self.target_mutation(Mutation_params().target_limit,Mutation_params().target_count_prob,Mutation_params().target_count_bias,Mutation_params().retarget_prob)
			#self.verify_network_consistency()
			self.potential_weights_mutation(Mutation_params().potential_prob,Mutation_params().potential_strength)
			#self.verify_network_consistency()
			self.threshold_mutation(Mutation_params().threshold_prob,Mutation_params().threshold_strength)
			#self.verify_network_consistency()
			self.type_mutation(input_count, output_count,Mutation_params().sensory_prob,Mutation_params().actuating_prob,Mutation_params().hidden_prob)
			#self.verify_network_consistency()
			self.neuron_count_mutation(input_count, output_count, Mutation_params().neuron_count_prob,Mutation_params().neuron_count_bias)
			#self.verify_network_consistency()
			self.reflex_pair_mutation()
			#self.correlator_mutation()
			self.verify_network_consistency()
	
	def mutation_stress_test(self,mutation_count):
		for i in range(mutation_count):
			if i % 100 == 0:
				print(str(i)  + ' MUTATIONS COMPLETED')
			self.default_mutation( Mutation_params().input_count, Mutation_params().output_count)
			self.verify_network_consistency()


      #### ##    ## ########  ##     ## ########
       ##  ###   ## ##     ## ##     ##    ##
       ##  ####  ## ##     ## ##     ##    ##
       ##  ## ## ## ########  ##     ##    ##
       ##  ##  #### ##        ##     ##    ##
       ##  ##   ### ##        ##     ##    ##
      #### ##    ## ##         #######     ##


	def input(self, inputs):
		self.neurons[0].excitation = self.neurons[0].activation_potential + 1 # activating the bias neuron



		for i in range(1, len(inputs) + 1 ):
			self.neurons[i].excitation = inputs[i-1] * (self.neurons[i].activation_potential + 1)
			

         ###    ########  ##     ##    ###    ##    ##  ######  ########
        ## ##   ##     ## ##     ##   ## ##   ###   ## ##    ## ##
       ##   ##  ##     ## ##     ##  ##   ##  ####  ## ##       ##
      ##     ## ##     ## ##     ## ##     ## ## ## ## ##       ######
      ######### ##     ##  ##   ##  ######### ##  #### ##       ##
      ##     ## ##     ##   ## ##   ##     ## ##   ### ##    ## ##
      ##     ## ########     ###    ##     ## ##    ##  ######  ########

		
	def advance(self, inputs, output_length):

		#assert not (self.neuron_count < 1 + len(inputs) + output_length)
		#self.input(inputs)
		sums = [0] * self.neuron_count
		outputs = [0] * output_length
		current_av_record = [[] for i in range(self.neuron_count)]

		for i,neuron in enumerate(self.neurons):

			#if neuron.fired:
			#	neuron.fired = 0
			#	if neuron.type == Brain_flags.NEURON_ACTUATING:
			#		outputs[neuron.external_index] += 1
	

			if neuron.type == Brain_flags.NEURON_ACTUATING:
				if neuron.fired:
					outputs[neuron.external_index] += 1
				else:
					outputs[neuron.external_index] -= 1


			neuron.fired = 0

			
			if( i == 0) or (self.hyperbolic_tangent(self.neurons[i].excitation) > self.neurons[i].activation_potential):
				for c in range (self.neurons[i].target_count):
					
					assert(self.neurons[i].targets[c] < self.neuron_count)
					sums[self.neurons[i].targets[c]] += self.neurons[i].potential_weights[c]
					#if i not in current_av_record[self.neurons[i].targets[c]]:
					#	current_av_record[self.neurons[i].targets[c]].append(i)

				
				self.neurons[i].fired = 1
				self.neurons[i].excitation = 0

			elif neuron.type == Brain_flags.NEURON_SENSORY:
				observation = inputs[neuron.external_index]
				if neuron.sensor_type == Brain_flags.SENSOR_BIT:
					if (observation >> neuron.external_bit) & 1:	
						for c in range (self.neurons[i].target_count):
					
							assert(self.neurons[i].targets[c] < self.neuron_count)
							sums[self.neurons[i].targets[c]] += self.neurons[i].potential_weights[c]
							#if i not in current_av_record[self.neurons[i].targets[c]]:
							#	current_av_record[self.neurons[i].targets[c]].append(i)
						self.neurons[i].fired = 1
						self.neurons[i].excitation = 0.0
				elif self.neurons[i].sensor_type == Brain_flags.SENSOR_LINEAR_THRESHOLD_UP:
					if observation >= neuron.external_thresh:
						for c in range (self.neurons[i].target_count):
					
							assert(self.neurons[i].targets[c] < self.neuron_count)
							sums[self.neurons[i].targets[c]] += self.neurons[i].potential_weights[c]
							#if i not in current_av_record[self.neurons[i].targets[c]]:
								#current_av_record[self.neurons[i].targets[c]].append(i)
						self.neurons[i].fired = 1
						self.neurons[i].excitation = 0.0
				elif self.neurons[i].sensor_type == Brain_flags.SENSOR_LINEAR_THRESHOLD_DOWN:
					if observation <= neuron.external_thresh:
						for c in range (self.neurons[i].target_count):
					
							assert(self.neurons[i].targets[c] < self.neuron_count)
							sums[self.neurons[i].targets[c]] += self.neurons[i].potential_weights[c]
						#	if i not in current_av_record[self.neurons[i].targets[c]]:
							#	current_av_record[self.neurons[i].targets[c]].append(i)
						self.neurons[i].fired = 1
						self.neurons[i].excitation = 0.0
				elif self.neurons[i].sensor_type == Brain_flags.SENSOR_BINARY:
					if observation != 0:
						for c in range (self.neurons[i].target_count):
					
							assert(self.neurons[i].targets[c] < self.neuron_count)
							sums[self.neurons[i].targets[c]] += self.neurons[i].potential_weights[c]
							#if i not in current_av_record[self.neurons[i].targets[c]]:
							#	current_av_record[self.neurons[i].targets[c]].append(i)
						self.neurons[i].fired = 1
						self.neurons[i].excitation = 0.0
			self.neurons[i].excitation = self.neurons[i].excitation/2.0
		
		for i in range(self.neuron_count):
			self.neurons[i].excitation += sums[i]
			#self.neurons[i].add_activation(current_av_record[i])


		#assert(len(inputs) + output_length + 1 <= self.neuron_count )
		#start = len(inputs) + 1
		#outputs = [0]
		#for i in range(output_length):
		#	outputs.append(self.neurons[start + i].fired)
		
		


		for i in range(len(outputs)):
			if outputs[i] > 0:
				outputs[i] = 1
			else:
				outputs[i] = 0
		return outputs



	def advance_n_with_mode(self, inputs, output_length, n_iterations, visualization_flag):
		results = []
		for i in range(n_iterations):
			results.append(self.advance(inputs,output_length))
			if visualization_flag == visualization.Visualization_flags.VISUALIZATION_ON:
				visualization.visualize_brain(print_brain_to_json(self))	

		return utils.extract_output_modes(results)


 ######  ########   #######   ######   ######   #######  ##     ## ######## ########
##    ## ##     ## ##     ## ##    ## ##    ## ##     ## ##     ## ##       ##     ##
##       ##     ## ##     ## ##       ##       ##     ## ##     ## ##       ##     ##
##       ########  ##     ##  ######   ######  ##     ## ##     ## ######   ########
##       ##   ##   ##     ##       ##       ## ##     ##  ##   ##  ##       ##   ##
##    ## ##    ##  ##     ## ##    ## ##    ## ##     ##   ## ##   ##       ##    ##
 ######  ##     ##  #######   ######   ######   #######     ###    ######## ##     ##

def cross_over(brain_1, brain_2):

	output = copy.deepcopy(brain_1)
	offset = output.neuron_count
	for neuron in brain_2.neurons:
		replica = copy.deepcopy(neuron)
		for i in range(replica.target_count):
			replica.targets[i] += offset
		output.neurons.append(replica)
	output.neuron_count += brain_2.neuron_count

	output.verify_network_consistency()
	return output






####       ##  #######
 ##       ##  ##     ##
 ##      ##   ##     ##
 ##     ##    ##     ##
 ##    ##     ##     ##
 ##   ##      ##     ##
#### ##        #######



def print_brain_to_json(brain):
	data = {}
	data['neuronCount'] = len(brain.neurons)
	data['neurons'] = []
	for neuron in brain.neurons:
		neuron_dict = {}
		neuron_dict['targets'] = neuron.targets
		neuron_dict['weights'] = neuron.potential_weights
		neuron_dict['thresh'] = neuron.activation_potential
		neuron_dict['targetCount'] = neuron.target_count

		neuron_dict['neuronType'] = neuron.type.name
		neuron_dict['sensorType'] = neuron.sensor_type.name

		neuron_dict['fired'] = neuron.fired

		neuron_dict['externalIndex'] = neuron.external_index
		neuron_dict['externalThreshold'] = neuron.external_thresh
		neuron_dict['externalBit'] = neuron.external_bit
		data['neurons'].append(neuron_dict)

	output = json.dumps(data, indent = 4)
	return output



def print_brain_to_file(brain):

	output = print_brain_to_json(brain)
	output_file = open('log.txt', 'w')
	output_file.write(output)
	output_file.close()





def load_brain_from_file(file_name):
	with open(file_name) as json_file:
		brain_json = json.load(json_file)
		load_brain = Brain()
		load_brain.neurons = []
		load_brain.neuron_count = brain_json['neuronCount']
		for neuron_json in brain_json['neurons']:
			new_neuron = Neuron()
			new_neuron.targets = neuron_json['targets']

			new_neuron.potential_weights = neuron_json['weights'] 
			new_neuron.activation_potential = neuron_json['thresh'] 
			new_neuron.target_count = neuron_json['targetCount']

			new_neuron.type = Brain_flags[neuron_json['neuronType']] 
			new_neuron.sensor_type = Brain_flags[neuron_json['sensorType']]



			new_neuron.external_index = neuron_json['externalIndex'] 
			new_neuron.external_thresh =neuron_json['externalThreshold'] 
			new_neuron.external_bit = neuron_json['externalBit'] 
			load_brain.neurons.append(new_neuron)
		return load_brain
			 	



