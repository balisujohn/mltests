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
    
        

if __name__ == '__main__':
    unittest.main()