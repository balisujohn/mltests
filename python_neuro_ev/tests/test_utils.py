import unittest
from unittest.mock import patch
import sys
import os
sys.path.insert(0,"./base_SNN")
import utils 

class Test_Utils(unittest.TestCase):

    def test_extract_output_modes(self):
        input = [[1,0,0],[1,1,0],[0,0,1],[1,0,1]]
        expected_output = [1,0,1]
        result = utils.extract_output_modes(input)
        self.assertEqual(result, expected_output)
    

    def test_binary_array_to_decimal(self):
        input = [1,0,1,0,0,1]
        expected_output = 41
        self.assertEqual(utils.binary_array_to_decimal(input), expected_output)
        input = [1,0,1,0,1,0]
        expected_output = 42
        self.assertEqual(utils.binary_array_to_decimal(input), expected_output)
        input = [1,1,0,0,1,1]
        expected_output = 51
        self.assertEqual(utils.binary_array_to_decimal(input), expected_output)


    def test_decimal_to_binary_array(self):
        input = 41
        expected_output = [1,0,1,0,0,1] 
        self.assertEqual(utils.decimal_to_binary_array(input), expected_output)
        input = 40
        expected_output = [1,0,1,0,0,0] 
        self.assertEqual(utils.decimal_to_binary_array(input), expected_output)
        input = 0
        expected_output = [0] 
        self.assertEqual(utils.decimal_to_binary_array(input), expected_output)
        input = 0
        expected_output = [0,0,0] 
        self.assertEqual(utils.decimal_to_binary_array(input, fixed_length = True, length = 3), expected_output)
        input = 1
        expected_output = [0,0,1] 
        self.assertEqual(utils.decimal_to_binary_array(input, fixed_length = True, length = 3), expected_output)
        input = 2
        expected_output = [0,1,0] 
        self.assertEqual(utils.decimal_to_binary_array(input, fixed_length = True, length = 3), expected_output)
        input = 3
        expected_output = [0,1,1] 
        self.assertEqual(utils.decimal_to_binary_array(input, bounded = True, bound = 7, fixed_length = True, length = 3), expected_output)
        input = 7
        expected_output = [1,1,1] 
        self.assertEqual(utils.decimal_to_binary_array(input, bounded = True, bound = 7, fixed_length = True, length = 3), expected_output)
        input = 87
        expected_output = [1,1,1] 
        self.assertEqual(utils.decimal_to_binary_array(input, bounded = True, bound = 7, fixed_length = True, length = 3), expected_output)


if __name__ == '__main__':
    unittest.main()