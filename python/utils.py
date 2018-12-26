import gym



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
	return  sorted(range(len(frequencies)), key = lambda x: frequencies[x])[-n:]


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
	



#frequencies = observation_frequency_analysis('SpaceInvaders-ram-v0',1000)
#print(frequencies)
#top_indices = top_n_frequency_indices(frequencies, 20)
#print(top_indices)


