import gym
from time import sleep 
from enum import Enum
from os import system, name 





#takes sleep time in seconds after clearing as an argument
def clear(sleep_time): 
  
	if name == 'nt': 
		_ = system('cls')
	else: 
		_ = system('clear') 
	sleep(sleep_time)

def comma_join_int(int1, int2):
	return str(int1) + ',' +  str(int2)

def observation_frequency_analysis(world_name, frames):
	env = gym.make(world_name)
	example = env.reset()
	frequencies = [0] * len(example)

	for c in range(10):	
		new_observation = env.reset()
		observation = new_observation
	
		for i in range(frames):
			action = env.action_space.sample()
			new_observation,reward,done,info = env.step(action)
			for index, value in enumerate(new_observation):
				if value != observation[index]:
					frequencies[index] +=1
			observation = new_observation


			if done:
				break
	return frequencies


def top_n_frequency_indices(frquencies,n):
	return sorted(range(len(frequencies)), key = lambda x: frequencies[x])[-n:]


def extract_observations(indices, observations):
	output = []	
	for index in indices:

		temp = [int(x) for x in bin(observations[index])[2:]]
		while len(temp) < 8:
			temp.insert(0,0) #adding 0 to beginning of list
		output.extend(temp)
	return output

def binary_array_to_decimal(array):
	result = 0
	index = 0
	for index, digit in enumerate(array):
		if digit == 1:		
			result += pow(2, (len(array)-1) - index)

	return result

def decimal_to_binary_array(integer, bounded= False, bound = 0, fixed_length = False, length = 0):
	if integer == 0:
		if fixed_length:
			return [0 for i in range(length)]
		else:
			return [0]
	if bounded and integer > bound:
		integer = bound
	result = []
	while integer != 0:
		result.insert(0,integer & 1)
		integer = integer >> 1
	if fixed_length:
		if len(result) > length:
			result = result[length:]
		elif len(result) < length:
			result =  [0 for i in range(length- len(result))] + result 

	return result 


	
###
# output is a list of lists, we return the mode of each list position across the lists
#
###
def extract_output_modes(output):
	result = [0]  * len(output[0])
	for i in range(len(output[0])):
		ones = 0
		zeros = 0
		for c in range(len(output)):
			if output[c][i] == 1:
				ones += 1
			else: 
				zeros += 1
		if ones >= zeros:
			result[i] = 1
		else: 
			result[i] = 0
	return result 



#frequencies = observation_frequency_analysis('SpaceInvaders-ram-v0',1000)
#print(frequencies)
#top_indices = top_n_frequency_indices(frequencies, 20)
#print(top_indices)


