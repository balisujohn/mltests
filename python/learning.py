import brain
from enum import Enum
import copy
from random import randrange
import utils
import gym

class Learning_flags(Enum):
	VISUALIZATION_ON = 1
	VISUALIZATION_OFF = 2

	
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


	if visualization_mode == Learning_flags.VISUALIZATION_ON:
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

def evalute_pendulum_cart_performance(brain, visualization_mode):
	
	env = gym.make('SpaceInvaders-ram-v0')
	observations = env.reset()
	score = 0.0
	desired_score = 1500
	while 1:
		score += 1
		if visualization_mode == Learning_flags.VISUALIZATION_ON:
			env.render()


		output = [0] * 3
		#inputs = utils.extract_observations(top_indices, observations)
		


		for i in range(1):
			output = brain.advance(observations, 3)
		
		action = min(utils.binary_array_to_decimal(output), 5)

		if visualization_mode == Learning_flags.VISUALIZATION_ON:
			print('ACTION: ' + str(action))
		
		observations,reward,done,info = env.step(action)
		if done:
			return (score/desired_score) * 100



def evaluate_space_invaders_performance(brain, visualization_mode):

	#top_indices = [87, 79, 80, 77, 112, 1, 8, 72, 6, 28, 3, 110, 82, 85, 78, 9, 81, 90, 106, 74]
	
	env = gym.make('SpaceInvaders-ram-v0')
	observations = env.reset()
	score = 0.0
	desired_score = 1000
	while 1:
		#score += 1
		if visualization_mode == Learning_flags.VISUALIZATION_ON:
			env.render()


		output = [0] * 3
		#inputs = utils.extract_observations(top_indices, observations)
		


		for i in range(1):
			output = brain.advance(observations, 3)

		
		action = min(utils.binary_array_to_decimal(output), 5)

		if visualization_mode == Learning_flags.VISUALIZATION_ON:
			print('ACTION: ' + str(action))
		
		observations,reward,done,info = env.step(action)
		score += reward
		if done:
			env.close()
			return (score/desired_score) * 100
		
		


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
	



def visualize_performance(brain, eval_function):
	while 1:
		eval_function(brain, Learning_flags.VISUALIZATION_ON)	


def learn(eval_function,input_size, output_size):

	best_brain = brain.Brain(1)

	best_score = 0
	
	counter = 0 	
	average = 0	
	
	while best_score < 100:

		counter += 1
		score = 0
		
		mutant = copy.deepcopy(best_brain) 


		for i in range(randrange(3)):
			mutant.default_mutation(input_size,output_size)

		test_instance = copy.deepcopy(mutant)

		score = eval_function(test_instance, Learning_flags.VISUALIZATION_OFF)

		#print(score)

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
		

def learn_from_existing(existing_brain, eval_function,input_size, output_size):

	best_brain = existing_brain
	benchmark_instance = copy.deepcopy(best_brain)
	best_score = eval_function(benchmark_instance, Learning_flags.VISUALIZATION_OFF)
	print('NEW BEST SCORE: ' + str(best_score))
	
	counter = 0
	average = 0	
	
	while best_score < 100:

		counter += 1
		score = 0
		
		mutant = copy.deepcopy(best_brain) 


		for i in range(randrange(3)):
			mutant.default_mutation(input_size,output_size)

		test_instance = copy.deepcopy(mutant)

		score = eval_function(test_instance, Learning_flags.VISUALIZATION_OFF)
		
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
		
				


