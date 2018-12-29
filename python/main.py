import learning
import brain
import sys
#import gym 


#env = gym.make()


#load_brain = brain.load_brain_from_file()
#result = learning.learn_from_existing(load_brain, learning.evaluate_space_invaders_performance,128,3)
#learning.visualize_performance(load_brain, learning.evaluate_space_invaders_performance)



if len(sys.argv) == 2 and sys.argv[1] == 'train':
	result = learning.learn(learning.evaluate_xor_performance, 2, 1)

elif len(sys.argv) == 3 and sys.argv[1] == 'analyze':
	load_brain = brain.load_brain_from_file(sys.argv[2])
	learning.visualize_performance(load_brain, learning.evaluate_xor_performance)
elif len(sys.argv) == 3 and sys.argv[1] == 'improve':
	load_brain = brain.load_brain_from_file(sys.argv[2])
	result = learning.learn_from_existing(load_brain, learning.evaluate_xor_performance,2,1)
else:
	print('INVALID USAGE')
	
