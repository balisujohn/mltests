import sys
sys.path.insert(0,"./base_SNN")
sys.path.insert(0,"./mega_grid")
import learning
import brain
import visualization
from mega_grid import init_mega_grid_params
import gym 
import logging

#John Balis 2019
#for support email balisujohn@gmail.com



#parameterizations for various evaluation environments

def set_solo_mega_grid_params():
	init_mega_grid_params()


def set_potion_store_params(): # make sure you update the variables in the learning function if you update input_count here
	brain.Mutation_params.set_mutation_to_default_1(brain.Mutation_params)
	brain.Mutation_params.input_count = 8
	brain.Mutation_params.mutation_cycles = 5
	brain.Mutation_params.output_count = 1
	brain.Mutation_params.neuron_count_bias = .9
	brain.Mutation_params.reflex_pair_prob = .1
	brain.Mutation_params.target_count_bias = .75

	brain.Mutation_params.upper_input_bounds = [.00000001] * 8
	brain.Mutation_params.lower_input_bounds = [-.000000001] * 8



def set_space_invaders_params():
	brain.Mutation_params.set_mutation_to_default_1(brain.Mutation_params)
	brain.Mutation_params.input_count = 128
	brain.Mutation_params.output_count = 3
	brain.Mutation_params.upper_input_bounds = [1] * 128
	brain.Mutation_params.lower_input_bounds = [-1] * 128

def set_pong_params():
	brain.Mutation_params.set_mutation_to_default_1(brain.Mutation_params)
	brain.Mutation_params.reflex_pair_prob=.2
	brain.Mutation_params.input_count = 128
	brain.Mutation_params.output_count = 3
	brain.Mutation_params.upper_input_bounds = [1] * 128
	brain.Mutation_params.lower_input_bounds = [-1] * 128


def set_cart_pole_params(): ##future ready dependent on mutations defaults 1
	brain.Mutation_params.set_mutation_to_default_1(brain.Mutation_params)
	brain.Mutation_params.reflex_pair_prob = .25
	brain.Mutation_params.target_count_bias = .7
	brain.Mutation_params.input_count = 4
	brain.Mutation_params.output_count = 1
	brain.Mutation_params.upper_input_bounds = [.00000001] * 4
	brain.Mutation_params.lower_input_bounds = [-.000000001] * 4


def set_xor_params(): ##future ready dependent on mutations defaults 1
	brain.Mutation_params.set_mutation_to_default_1(brain.Mutation_params)
	brain.Mutation_params.input_count = 2
	brain.Mutation_params.output_count = 1
	brain.Mutation_params.neuron_count_bias = .5
	brain.Mutation_params.reflex_pair_prob = 0
	brain.Mutation_params.upper_input_bounds = [1] * 2
	brain.Mutation_params.lower_input_bounds = [-1] * 2


def set_berzerk_params():
	brain.Mutation_params.set_mutation_to_default_1(brain.Mutation_params)
	brain.Mutation_params.input_count = 128
	brain.Mutation_params.output_count = 5
	brain.Mutation_params.upper_input_bounds = [1] * 128
	brain.Mutation_params.lower_input_bounds = [-1] * 128


def set_biped_params():
	brain.Mutation_params.set_mutation_to_default_1(brain.Mutation_params)
	brain.Mutation_params.input_count = 24
	brain.Mutation_params.output_count = 8
	brain.Mutation_params.upper_input_bounds = [.00000001] * 24
	brain.Mutation_params.lower_input_bounds = [-.00000001] * 24
	brain.Mutation_params.mutation_cycles = 4
	brain.Mutation_params.reflex_pair_prob = .05


def set_chopper_params():
	brain.Mutation_params.set_mutation_to_default_1(brain.Mutation_params)
	brain.Mutation_params.input_count = 128
	brain.Mutation_params.output_count = 5
	brain.Mutation_params.upper_input_bounds = [1] * 128
	brain.Mutation_params.lower_input_bounds = [-1] * 128

def set_stress_test_params():
	brain.Mutation_params.set_mutation_to_default_1(brain.Mutation_params)
	brain.Mutation_params.input_count = 100
	brain.Mutation_params.output_count = 100
	brain.Mutation_params.upper_input_bounds = [.000000001] * 100
	brain.Mutation_params.lower_input_bounds = [-.000000001] * 100


environments ={
'invaders':learning.evaluate_space_invaders_performance,
'cartpole':learning.evalute_pendulum_cart_performance,
'xor':learning.evaluate_xor_performance,
'berzerk':learning.evaluate_berzerk_performance,
'chopper':learning.evaluate_chopper_performance,
'pong':learning.evaluate_pong_performance,
'pshoppe':learning.evaluate_potion_store_performance,
'biped':learning.evaluate_biped_performance,
'sologrid':learning.evaluate_solo_mega_grid_performance
}



environment_settings= {
'invaders':set_space_invaders_params,
'cartpole':set_cart_pole_params,
'xor':set_xor_params,
'berzerk':set_berzerk_params,
'chopper':set_chopper_params,
'pong':set_pong_params,
'pshoppe':set_potion_store_params,
'biped':set_biped_params,
'sologrid':set_solo_mega_grid_params

}


learning_techniques = {
'default':learning.learn,
'population':learning.population_learn,
'imp':learning.impatient_learn
}

# test mode for development purposes
if sys.argv[1] == 'test':
	set_space_invaders_params()
	b = brain.Brain(1)
	b.reflex_pair_mutation()
	test_result = learning.visualize_performance(b,learning.evaluate_space_invaders_performance)







#core user interface dialouge

logging.disable(999999999999999)

if len(sys.argv) == 3 and sys.argv[1] == 'stress':
	mutation_count = int(sys.argv[2])
	set_stress_test_params()
	b = brain.Brain(1)
	b.mutation_stress_test(mutation_count)

elif len(sys.argv) == 4 and sys.argv[1] == 'train':
	param_setup = environment_settings[sys.argv[2]]
	learning_algorithm = learning_techniques[sys.argv[3]]	
	param_setup()
	result = learning_algorithm(None, environments[sys.argv[2]])

elif len(sys.argv) == 4 and sys.argv[1] == 'analyze':
	load_brain = brain.load_brain_from_file(sys.argv[3])
	param_setup = environment_settings[sys.argv[2]]
	param_setup()
	learning.visualize_performance(load_brain, environments[sys.argv[2]])

elif len(sys.argv) == 5 and sys.argv[1] == 'improve':
	load_brain = brain.load_brain_from_file(sys.argv[4])
	learning_algorithm = learning_techniques[sys.argv[3]]	
	param_setup = environment_settings[sys.argv[2]]
	param_setup()
	result = learning_algorithm(load_brain, environments[sys.argv[2]])
else:
	print('INVALID USAGE')
	
