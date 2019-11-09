import sys
sys.path.insert(0,".")
sys.path.insert(0,"./base_SNN")
sys.path.insert(0,"./mega_grid")
import pprint
import brain
import logging
from enum import Enum
import os
import copy
from random import randrange
from random import uniform 
import utils
from utils import clear
import gym
import mega_grid
import visualization
from itertools import combinations 


#John Balis 2019
#for support email balisujohn@gmail.com





def evaluate_solo_mega_grid_performance(brain, visualization_mode):
	# We will see how long our agent survives on average over 10 trials of 1000 frames of time

	trials = 100
	frame_limit = 1000

	score = 0.0

	for i in range(trials):
		test_instance = copy.deepcopy(brain)
		mega_grid.init_mega_grid_params()
		grid = mega_grid.Grid(20)
		grid.add_agent((3,4))
		agent = grid.agents[(3,4)]
		grid.agents[(3,4)].brain = test_instance
		grid.passive_physics()
		for c in range(frame_limit):
			if agent.energy <= 0:
				break
			score = score + 1
			grid.advance_agents(visualization_mode)
			grid.active_physics()
			if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
				grid.visualize_detailed_grid()
				pprint.pprint(grid.info)
				print(agent.energy)
				clear(.0001)
		
	return score/ (trials * frame_limit) * 100
			





#solved by save.4 in topologies/xor
# evaluates performance on neural network on xoring inputs
def evaluate_xor_performance(brain, visualization_mode):
	test_instance_1 = copy.deepcopy(brain)		
	test_instance_2 = copy.deepcopy(brain)
	test_instance_3 = copy.deepcopy(brain)
	test_instance_4 = copy.deepcopy(brain)

	[input_1,input_2,input_3,input_4] = [[0,0],[0,1],[1,0],[1,1]]

	[goal_1,goal_2,goal_3,goal_4] = [0,1,1,0]


	output_1 = 0
	output_2 = 0
	output_3 = 0
	output_4 = 0

	for i in range(5):
		output_1 = test_instance_1.advance(input_1,1) 
		output_2 = test_instance_2.advance(input_2,1)
		output_3 = test_instance_3.advance(input_3,1)
		output_4 = test_instance_4.advance(input_4,1)


	if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
		print('')
		print('INPUTS: '+ str([input_1,input_2,input_3,input_4]))
		print('OUTPUTS: ' + str([output_1, output_2, output_3,output_4]))




	score = 0
	if output_1[0] == goal_1:
		score += 25
	if output_2[0] == goal_2:
		score += 25
	if output_3[0] == goal_3:
		score += 25
	if output_4[0] == goal_4:
		score += 25


	return score


#solved by save.12 in topologies/cartpole
#openAI Gym implementation of pendulum cart
def evalute_pendulum_cart_performance(test_brain, visualization_mode):
	
	
	total_score = 0.0
	desired_score = 200
	trials = 100
	for c in range(trials):
		env = gym.make('CartPole-v0')
		observations = env.reset()
		test_instance = copy.deepcopy(test_brain)
		score = 0
		while True:#for h in range(desired_score):
			#score += 1
			if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
				env.render()


			output = [0] * 3

		

			for i in range(len(observations)):
				brain.Mutation_params().upper_input_bounds[i] = max(brain.Mutation_params().upper_input_bounds[i],observations[i])
				brain.Mutation_params().lower_input_bounds[i] = min(brain.Mutation_params().lower_input_bounds[i],observations[i])


			sum = 0
			for i in range(5):
				sum += test_instance.advance(observations, 1)[0]
				if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON: 
					visualization.visualize_brain(brain.print_brain_to_json(test_instance))	
			action = int(sum >=3)

			if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
				print('ACTION: ' + str(action))
				

		
		
			observations,reward,done,info = env.step(action)
			score += reward
			if done:
				total_score += score
				break
		env.close()
	return (total_score / (trials * desired_score)) * 100




#unsolved 
#evaluates space invaders performance on an emulated Atari
def evaluate_space_invaders_performance(test_brain, visualization_mode):

	#top_indices = [87, 79, 80, 77, 112, 1, 8, 72, 6, 28, 3, 110, 82, 85, 78, 9, 81, 90, 106, 74]
	


	best_score = 0.0
	desired_score = 1000
	brain_speed = 5
	trials = 100
	output_count = 3
	for i in range(trials):
		env = gym.make('SpaceInvaders-ram-v0')
		test_instance = copy.deepcopy(test_brain)
		observations = env.reset()
		score = 0
		while 1:
			#score += 1
			if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
				env.render()



			output = [0] * output_count
			#inputs = utils.extract_observations(top_indices, observations)
		

			for i in range(len(observations)):
				brain.Mutation_params().upper_input_bounds[i] = max(brain.Mutation_params().upper_input_bounds[i],observations[i])
				brain.Mutation_params().lower_input_bounds[i] = min(brain.Mutation_params().lower_input_bounds[i],observations[i])


			raw_output = []
			for i in range(brain_speed):
				raw_output.append ( test_instance.advance(observations, 3))
				if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON: 
					visualization.visualize_brain(brain.print_brain_to_json(test_instance))	

			for i in range(output_count):
				for c in range(brain_speed):	
					output[i] += raw_output[c][i]
				output[i] = int(output[i] > int(brain_speed/2))	



			action = min(utils.binary_array_to_decimal(output), 5)

			if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
				print('ACTION: ' + str(action))
		
			observations,reward,done,info = env.step(action)
			score += reward
			if done:
				best_score += score 
				env.close()
				break
				

	return (best_score/(desired_score* trials)) * 100

#unsolved
#evaluates space pong performance on an emulated Atari
def evaluate_pong_performance(test_brain, visualization_mode):

	#top_indices = [87, 79, 80, 77, 112, 1, 8, 72, 6, 28, 3, 110, 82, 85, 78, 9, 81, 90, 106, 74]
	


	best_score = 0
	desired_score = 2000.0
	brain_speed = 5
	trials = 100
	output_count = 3
	for i in range(trials):
		env = gym.make('Pong-ram-v0')
		test_instance = copy.deepcopy(test_brain)
		observations = env.reset()
		score = 0
		while 1:
			
			#score += 1
			if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
				env.render()



			output = [0] * output_count
			#inputs = utils.extract_observations(top_indices, observations)
		

			for i in range(len(observations)):
				brain.Mutation_params().upper_input_bounds[i] = max(brain.Mutation_params().upper_input_bounds[i],observations[i])
				brain.Mutation_params().lower_input_bounds[i] = min(brain.Mutation_params().lower_input_bounds[i],observations[i])


			raw_output = []
			for i in range(brain_speed):
				raw_output.append ( test_instance.advance(observations, 3))
				if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON: 
					visualization.visualize_brain(brain.print_brain_to_json(test_instance))	

			for i in range(output_count):
				for c in range(brain_speed):	
					output[i] += raw_output[c][i]
				output[i] = int(output[i] > int(brain_speed/2))	



			action = min(utils.binary_array_to_decimal(output), 5)

			if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
				print('ACTION: ' + str(action))
		
			observations,reward,done,info = env.step(action)
			score += 1#reward
			if done:
				best_score += score #+ 21
				env.close()
				break
		

	return ((best_score)/(desired_score* trials)) * 100



	
#unsolved
#evaluates berzerk performance on an emulated Atari
	
def evaluate_berzerk_performance(test_brain, visualization_mode):

	#top_indices = [87, 79, 80, 77, 112, 1, 8, 72, 6, 28, 3, 110, 82, 85, 78, 9, 81, 90, 106, 74]
	


	best_score = 0.0
	desired_score = 1000
	trials = 5
	brain_speed = 5
	output_count = 5
	for i in range(trials):
		test_instance = copy.deepcopy(test_brain)
		env = gym.make('Berzerk-ram-v0')
		observations = env.reset()
		score = 0
		for c in range(1000):
			#score += 1
			if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
				env.render()



			output = [0] * 5
			#inputs = utils.extract_observations(top_indices, observations)
		

			for i in range(len(observations)):
				brain.Mutation_params().upper_input_bounds[i] = max(brain.Mutation_params().upper_input_bounds[i],observations[i])
				brain.Mutation_params().lower_input_bounds[i] = min(brain.Mutation_params().lower_input_bounds[i],observations[i])



			raw_output = []
			for i in range(brain_speed):
				raw_output.append ( test_instance.advance(observations, 5))
				if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON: 
					visualization.visualize_brain(brain.print_brain_to_json(test_instance))	

			for i in range(output_count):
				for c in range(brain_speed):	
					output[i] += raw_output[c][i]
				output[i] = int(output[i] > int(brain_speed/2))	

		
			action = min(utils.binary_array_to_decimal(output), 17)

			if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
				print('ACTION: ' + str(action))
		
			observations,reward,done,info = env.step(action)
			score += reward
			if done:
				break
		best_score += score
		env.close()
	return (best_score/(desired_score* trials)) * 100
		
				
#unsolved
#evaluates chopper performance on an emulated Atari
def evaluate_chopper_performance(test_brain, visualization_mode):

	#top_indices = [87, 79, 80, 77, 112, 1, 8, 72, 6, 28, 3, 110, 82, 85, 78, 9, 81, 90, 106, 74]
	


	best_score = 0.0
	desired_score = 1000
	trials = 5
	output_count = 5
	brain_speed = 5
	for i in range(trials):
		env = gym.make('ChopperCommand-ram-v0')
		test_instance = copy.deepcopy(test_brain)
		observations = env.reset()
		score = 0
		for c in range(1000):
			#score += 1
			if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
				env.render()



			output = [0] * 5
			#inputs = utils.extract_observations(top_indices, observations)
		

			for i in range(len(observations)):
				brain.Mutation_params().upper_input_bounds[i] = max(brain.Mutation_params().upper_input_bounds[i],observations[i])
				brain.Mutation_params().lower_input_bounds[i] = min(brain.Mutation_params().lower_input_bounds[i],observations[i])



			raw_output = []
			for i in range(brain_speed):
				raw_output.append ( test_instance.advance(observations, 5))
				if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON: 
					visualization.visualize_brain(brain.print_brain_to_json(test_instance))	

			for i in range(output_count):
				for c in range(brain_speed):	
					output[i] += raw_output[c][i]
				output[i] = int(output[i] > int(brain_speed/2))

			action = min(utils.binary_array_to_decimal(output), 17)

			if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
				print('ACTION: ' + str(action))
		
			observations,reward,done,info = env.step(action)
			score += reward
			if done:
				break
		best_score += score
		env.close()
	return (best_score/(desired_score* trials)) * 100
		
				
	
#unsolved
#evaluates chopper performance on an emulated Atari
def evaluate_biped_performance(test_brain, visualization_mode):

	#top_indices = [87, 79, 80, 77, 112, 1, 8, 72, 6, 28, 3, 110, 82, 85, 78, 9, 81, 90, 106, 74]



	best_score = 0
	desired_score = 1000
	trials = 100
	output_count = 8
	brain_speed = 5
	for i in range(trials):
		

		env = gym.make('BipedalWalker-v2')
		test_instance = copy.deepcopy(test_brain)
		observations = env.reset()
		score = 0
		counter = 0
		while counter < 1000:
			counter += 1
			#score += 1
			if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
				env.render()



			output = [0] * 4
			#inputs = utils.extract_observations(top_indices, observations)
		

			for i in range(len(observations)):
				brain.Mutation_params().upper_input_bounds[i] = max(brain.Mutation_params().upper_input_bounds[i],observations[i])
				brain.Mutation_params().lower_input_bounds[i] = min(brain.Mutation_params().lower_input_bounds[i],observations[i])

			

			raw_output = []
			for i in range(brain_speed):
				raw_output.append ( test_instance.advance(observations, output_count))
				#if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON: 
				#	visualization.visualize_brain(brain.print_brain_to_json(test_instance))	

			for i in range(int(output_count/2)):
				for c in range(brain_speed):	
					output[i] += raw_output[c][i]
					output[i] -= raw_output[c][i + int(output_count/2)]

				output[i] = (output[i]/float(brain_speed))

			action = output
			
	
			



			if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
				print(counter)
				print('ACTION: ' + str(action))
		
			observations,reward,done,info = env.step(action)
			#if reward > 0:			
			score += reward
			if done:
				break
		best_score += score
		env.close()

	return ((best_score/(desired_score* trials)) * 100)		
				






#experimental instance that requires some degree of temporal learning to work
#Hypothesis is that it will be very difficult for the current architecture

def evaluate_potion_store_performance(test_brain, visualization_mode):




	time_limit = 200
	time = 0
	potion_count = 6
	health_potion_count = 2
	incorrect_limit = 5
	correct_limit = 100.0
	brain_speed = 5
	total_score = 0


	indices = [i for i  in range(potion_count)]
	coms = combinations(indices, health_potion_count)
	

	for com in coms:
		assert (health_potion_count <= potion_count)
		test_instance = copy.deepcopy(test_brain)

		health_potion_indices = com

		correct_potions = 0.0
		incorrect_potions = 0.0
	
		correct_bit = 0
		incorrect_bit = 0
		time = 0


		while correct_potions < correct_limit and incorrect_potions < incorrect_limit and time < time_limit:
			potion_offer = randrange(potion_count)
			input = [0] * potion_count
			input[potion_offer]  = 1
			input = [correct_bit, incorrect_bit] + input

			assert(len(input)== 8)

			output = 0
			for i in range(brain_speed):	
				output += test_instance.advance(input, 1)[0]
				if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON: 
					visualization.visualize_brain(brain.print_brain_to_json(test_instance))	

			
			output = int(output > int(brain_speed/2))
		


			if output:
				if (potion_offer not in health_potion_indices):
					incorrect_potions += 1
					incorrect_bit = 1
					correct_bit = 0
					if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
						print('DRANK ' + str(potion_offer) + ': POISION')
		
				else: 
					correct_potions += 1
					correct_bit = 1
					incorrect_bit = 0
					if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
						print('DRANK ' + str(potion_offer) + ': HEALTH POTION')

			else: 	
				correct_bit = 0
				incorrect_bit = 0
				if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
						print('DECLINED OFFER FOR ' + str(potion_offer))
		

			time += 1
			#if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
				#test_instance.print_activation_record()
		total_score += correct_potions
		if visualization_mode == visualization.Visualization_flags.VISUALIZATION_ON:
			print("NUMBER CORRECT: " + str(correct_potions))
	return float(total_score/(correct_limit*15)) * 100.0
			

		

	




#Deprecated, as this relies on an older network architecutre
def analyze(brain, input_count, output_count):
	while True:
		test_instance = copy.deepcopy(brain)
		
		inputs = str(raw_input("PLEASE ENTER " + str(input_count) + " INPUTS:\n"))
		inputs = [int(char) for char in inputs]
		#print (inputs)
		time_slices = int(input("PLEASE ENTER DESIRED NUMBER OF TIME SLICES:\n"))
		outputs = []
		for i in range(time_slices):
			outputs = self.advance(inputs, output_count)
		print ("OUTPUTS: " + str(outputs))
	


# visualization for when the system is run in analysis mode
def visualize_performance(brain, eval_function):
	while 1:
		eval_function(brain, visualization.Visualization_flags.VISUALIZATION_ON)	


# naive learning algorithm, starting from existing topology
def learn(existing_brain, eval_function):




	input_size = brain.Mutation_params().input_count
	output_size = brain.Mutation_params().output_count

	if existing_brain != None:
		best_brain = existing_brain
	else:
		best_brain = brain.Brain()
	benchmark_instance = copy.deepcopy(best_brain)
	best_score = eval_function(benchmark_instance, visualization.Visualization_flags.VISUALIZATION_OFF)
	print('NEW BEST SCORE: ' + str(best_score))
	
	counter = 0
	average = 0	
	
	while best_score < 100:

		counter += 1
		score = 0
		
		mutant = copy.deepcopy(best_brain) 


		for i in range(1):
			mutant.default_mutation(input_size,output_size)

		test_instance = copy.deepcopy(mutant)

		score = eval_function(test_instance, visualization.Visualization_flags.VISUALIZATION_OFF)
		
		average += score
		if ((counter % 100) == 0):
			print ('LAST 100 AVERAGE: ' + str(average/100))		
			average = 0
		if score >= best_score:
			print('NEW BEST SCORE: ' + str(score))
			brain.print_brain_to_file(mutant)

			best_score = score

			best_brain = copy.deepcopy(mutant)

	

	return best_brain
		

#population-based learning algorithm, with crossover. Experimental

def population_learn(existing_brain, eval_function):
	
	population_size  = brain.Mutation_params().population_size
	input_size = brain.Mutation_params().input_count
	output_size = brain.Mutation_params().output_count


	population = []

	if existing_brain == None:
		for i in range(population_size):
			population.append( [0,brain.Brain()] )
	else:
		for i in range(population_size):
			population.append( [0,copy.deepcopy(existing_brain)] )

	
	best_score = float("-inf")
	best_brain = None


	while best_score < 100:

		for i in range(len(population)):
			test_instance = copy.deepcopy(population[i][1])
			population[i][0] = eval_function(test_instance,  visualization.Visualization_flags.VISUALIZATION_OFF) 
			if population[i][0] >= best_score:
				best_score = population[i][0]
				best_brain = population[i][1]
		
		#print(len(population))
		population = sorted(population, key= lambda x : -x[0])
		population = population[:population_size]
		#print(len(population))

		print('\nSCORES: '),
		for p in population:
			print(str(p[0]) + ',' ) ,

		for i in range(population_size):

			new_pair = [randrange(population_size), randrange(population_size)]
			while new_pair[0] == new_pair[1]:

				new_pair[1] = randrange(population_size)

	
			
			#print(population[new_pair[0]][1])
			#print(population[new_pair[1]][1])
			new_offspring = brain.cross_over(population[new_pair[0]][1], population[new_pair[1]][1])
			new_offspring.verify_network_consistency()		
			new_offspring.default_mutation(input_size, output_size)
			population.append([0,new_offspring])

	
		
# impatient_learning_algorithm
def impatient_learn(existing_brain, eval_function):




	input_size = brain.Mutation_params().input_count
	output_size = brain.Mutation_params().output_count

	if existing_brain != None:
		best_brain = existing_brain
	else:
		best_brain = brain.Brain()
	benchmark_instance = copy.deepcopy(best_brain)

	best_score = eval_function(benchmark_instance, visualization.Visualization_flags.VISUALIZATION_OFF)
	print('NEW BEST SCORE: ' + str(best_score))
	
	counter = 0
	average = 0	

	chaos = 1.0
	chaos_ceiling = 5.0
	
	while best_score < 100:

		counter += 1
		score = 0
		
		mutant = copy.deepcopy(best_brain) 


		for i in range(1):
			mutant.default_mutation(input_size,output_size)

		test_instance = copy.deepcopy(mutant)

		score = eval_function(test_instance, visualization.Visualization_flags.VISUALIZATION_OFF)
		
		average += score
		if ((counter % 100) == 0):
			print ('LAST 100 AVERAGE: ' + str(average/100))
			print('CHAOS: ' + str(chaos))		
			#if uniform(0,1) > .5:
		#		print('SUPRESSING MUTATION')
		#		brain.Mutation_params().supress_mutation()
		#	else:	
		#		print('AMPLIFYING MUTATION')
		#		brain.Mutation_params().amplify_mutation()
			average = 0
		if score >= best_score:
			chaos = 1
			print('NEW BEST SCORE: ' + str(score))
			brain.print_brain_to_file(mutant)

			best_score = score

			best_brain = copy.deepcopy(mutant)
		elif chaos < chaos_ceiling:
			chaos += .01
		brain.Mutation_params().mutation_cycles = randrange(int(chaos)) + 1
	

	return best_brain
		
	





				


