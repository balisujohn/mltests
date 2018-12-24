import gym



def observation_frequency_analysis(world_name, frames):
	env = gym.make(world_name)
	example = env.reset()
	frequencies = [0] * len(example)

	for c in range(100):	
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



print(observation_frequency_analysis('SpaceInvaders-ram-v0',1000))
