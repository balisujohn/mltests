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

        

if __name__ == '__main__':
    unittest.main()