import unittest
from unittest.mock import patch , call
import sys
import os
sys.path.append(os.path.join(os.path.dirname(__file__), "../mega_grid"))
from mega_grid import *


class test_grid(unittest.TestCase):
    
    def test_norm_dict(self):
        grid = Grid(10)
        example_dict_1 = {'key1': 2, 'key2':4,'key3':6}
        result_dict_1 = {'key1': 2.0/12, 'key2':4.0/12,'key3':6.0/12}
        result = grid.norm_dict(example_dict_1)
        self.assertDictEqual(result_dict_1, result)

        grid = Grid(10)
        example_dict_1 = {'key1': 2, 'key2':4,'key3':6}
        result_dict_1 = {'key1': 2.0/13, 'key2':4.0/12,'key3':6.0/12}
        result = grid.norm_dict(example_dict_1)
        self.assertNotEqual(result_dict_1, result)


    def test_grid_init(self):
        size = 10
        desired_shape = (size,size)
        grid = Grid(size)
        self.assertEqual(grid.sector_size,size)
        self.assertEqual(grid.grid.shape, desired_shape)


    @patch('mega_grid.uniform')
    def test_passive_cell_update(self, mock_uniform):

        grid = Grid(1)
        offsets = {Object_type.CAPSULE:.4, Object_type.AGENT: .6}
        baseline_densities = {Object_type.CAPSULE:.1, Object_type.AGENT: .5}
        mock_uniform.side_effect = [.2,.7]
        grid.grid[0][0] = Object_type.EMPTY
        result = grid.passive_cell_update(grid.grid[0][0], offsets, baseline_densities)
        self.assertEqual(result , Object_type.CAPSULE)
       
        mock_uniform.side_effect = [.2,.1]
        grid.grid[0][0] = Object_type.EMPTY
        result = grid.passive_cell_update(grid.grid[0][0], offsets, baseline_densities)
        self.assertEqual(result , Object_type.AGENT)

        mock_uniform.side_effect = [.9,.1]
        grid.grid[0][0] = Object_type.EMPTY
        result = grid.passive_cell_update(grid.grid[0][0], offsets, baseline_densities)
        self.assertEqual(result , Object_type.EMPTY)

    @patch('mega_grid.Grid.passive_cell_update')
    def test_passive_physics(self, mock_passive_cell_update):
        grid = Grid(2)
        mock_passive_cell_update.return_value = Object_type.CAPSULE
        grid.passive_physics()
        desired_result = [
            call.mock_passive_cell_update(0,{Object_type.EMPTY:  0.26, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25}, {Object_type.EMPTY:  0.74, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25}),
            call.mock_passive_cell_update(0,{Object_type.EMPTY:  0.26, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25}, {Object_type.EMPTY:  0.74, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25}),
            call.mock_passive_cell_update(0,{Object_type.EMPTY:  0.26, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25}, {Object_type.EMPTY:  0.74, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25}),
            call.mock_passive_cell_update(0,{Object_type.EMPTY:  0.26, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25}, {Object_type.EMPTY:  0.74, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25})
        ]
        self.assertEqual(desired_result, mock_passive_cell_update.mock_calls)
        for i in range(grid.sector_size):
            for c in range(grid.sector_size):
                self.assertEqual(grid.grid[i][c], int(Object_type.CAPSULE))

if __name__ == '__main__':
    unittest.main()