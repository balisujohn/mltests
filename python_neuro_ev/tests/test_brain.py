import unittest
from unittest.mock import patch
import sys
import os
sys.path.insert(0,"./base_SNN")
print(os.path.dirname(os.path.realpath(__file__)))

import brain 


class test_Brain(unittest.TestCase):
    
    def test_mutation_params_constructor(self):
        self.assertEqual(brain.Mutation_params().neuron_start_count, 1)
        self.assertEqual(brain.Mutation_params().swap_prob,.1)
        self.assertEqual(brain.Mutation_params().neuron_count_prob,.5)
        self.assertEqual(brain.Mutation_params().neuron_count_bias,.5)
        self.assertEqual(brain.Mutation_params().target_limit,5)
        self.assertEqual(brain.Mutation_params().target_count_prob,.25)
        self.assertEqual(brain.Mutation_params().target_count_bias,.5)
        self.assertEqual(brain.Mutation_params().retarget_prob,.25)
        self.assertEqual(brain.Mutation_params().potential_prob,.1)
        self.assertEqual(brain.Mutation_params().potential_strength,.1)
        self.assertEqual(brain.Mutation_params().threshold_prob,.1)
        self.assertEqual(brain.Mutation_params().threshold_strength,.1)
        self.assertEqual(brain.Mutation_params().reflex_pair_prob,.1)
        self.assertEqual(brain.Mutation_params().input_count,10)
        self.assertEqual(brain.Mutation_params().output_count, 10)

        self.assertEqual(brain.Mutation_params().sensory_prob, .25)
        self.assertEqual(brain.Mutation_params().actuating_prob, .25)
        self.assertEqual(brain.Mutation_params().hidden_prob, .1)
        
        self.assertEqual(brain.Mutation_params().mutation_cycles, 1)
        assert len(brain.Mutation_params().upper_input_bounds) is 0
        assert len(brain.Mutation_params().lower_input_bounds) is 0

    def test_mutation_params_default_1(self):

        param_instance = brain.Mutation_params()
        param_instance.swap_prob= 999
        param_instance.set_mutation_to_default_1()
        self.assertEqual(brain.Mutation_params().neuron_start_count, 1)
        self.assertEqual(param_instance.swap_prob,.1)
        self.assertEqual(param_instance.neuron_count_prob,.5)
        self.assertEqual(param_instance.neuron_count_bias,.5)
        self.assertEqual(param_instance.target_limit,5)
        self.assertEqual(param_instance.target_count_prob,.25)
        self.assertEqual(param_instance.target_count_bias,.5)
        self.assertEqual(param_instance.retarget_prob,.25)
        self.assertEqual(param_instance.potential_prob,.1)
        self.assertEqual(param_instance.potential_strength,.1)
        self.assertEqual(param_instance.threshold_prob,.1)
        self.assertEqual(param_instance.threshold_strength,.1)
        self.assertEqual(param_instance.reflex_pair_prob,0)
        self.assertEqual(param_instance.input_count,10)
        self.assertEqual(param_instance.output_count, 10)

        self.assertEqual(param_instance.sensory_prob, .25)
        self.assertEqual(param_instance.actuating_prob, .25)
        self.assertEqual(param_instance.hidden_prob, .1)
        
        self.assertEqual(param_instance.mutation_cycles, 1)
        assert len(param_instance.upper_input_bounds) is 0
        assert len(param_instance.lower_input_bounds) is 0

  
    @patch('brain.uniform')
    def test_neuron_constructor(self, mock_uniform):
            mock_uniform.return_value = .5
            instance = brain.Neuron()
            self.assertEqual(instance.activation_potential , .5)
            self.assertEqual(instance.target_count,0)
            assert len(instance.targets) == 0
            assert len(instance.potential_weights) == 0
            self.assertEqual(instance.fired, 0)
            self.assertEqual(instance.excitation, 0)
            self.assertEqual(instance.type, brain.Brain_flags.NEURON_HIDDEN)
            self.assertEqual(instance.sensor_type, brain.Brain_flags.SENSOR_BINARY)
            self.assertEqual(instance.external_index, 0)
            self.assertEqual(instance.external_thresh, 0)
            self.assertEqual(instance.external_bit, 0)

if __name__ == '__main__':
    unittest.main()