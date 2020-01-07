import unittest
from unittest.mock import patch , call
import sys
import os
sys.path.insert(0,"./mega_grid")
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
            call.mock_passive_cell_update(Object_type.EMPTY,{Object_type.EMPTY:  0.0, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25}, {Object_type.EMPTY:  0.74, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25}),
            call.mock_passive_cell_update(Object_type.EMPTY,{Object_type.EMPTY:  0.0, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25}, {Object_type.EMPTY:  0.74, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25}),
            call.mock_passive_cell_update(Object_type.EMPTY,{Object_type.EMPTY:  0.0, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25}, {Object_type.EMPTY:  0.74, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25}),
            call.mock_passive_cell_update(Object_type.EMPTY,{Object_type.EMPTY:  0.0, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25}, {Object_type.EMPTY:  0.74, Object_type.STRIDER:  0.01, Object_type.CAPSULE:  0.25})
        ]
        self.assertEqual(desired_result, mock_passive_cell_update.mock_calls)
        for i in range(grid.sector_size):
            for c in range(grid.sector_size):
                self.assertEqual(grid.grid[i][c], int(Object_type.CAPSULE))



    def test_sense(self):
        grid = Grid(3)
        grid.grid[0][1] = Object_type.CAPSULE
        grid.grid[2][0] = Object_type.STRIDER
        result1 = grid.sense((1,0), Direction.UP)
        self.assertEqual(result1, (0,0,0,0,0,0))
        result2 = grid.sense((1,1), Direction.UP)
        self.assertEqual(result2, (0,0,1,0,0,0))
        result3 = grid.sense((2,0), Direction.LEFT)
        self.assertEqual(result3, (0,0,1,0,0,0))
        result4 = grid.sense((0,0), Direction.RIGHT)
        self.assertEqual(result4, (0,0,1,0,0,0))
        result5 = grid.sense((0,0), Direction.DOWN)
        self.assertEqual(result5, (0,1,0,0,0,1))
        result6 = grid.sense((2,0), Direction.DOWN)
        self.assertEqual(result6, (0,0,0,0,1,0))
        result7 = grid.sense((2,2), Direction.LEFT)
        self.assertEqual(result7, (0,1,0,0,0,1))



    def test_add_agent(self):
        grid = Grid(3)
        grid.add_agent((0,1))
        self.assertEqual(grid.grid[1][0] , Object_type.AGENT)
        self.assertEqual(list(grid.agents.keys())[0], (0,1))
        self.assertEqual(grid.info[Object_type.AGENT], 1)
        self.assertEqual(grid.info[Object_type.EMPTY], 8)


    def test_remove_agent(self):
        grid = Grid(3)
        grid.grid[1][0] = int(Object_type.AGENT)
        grid.agents[(0,1)] = {"dummy": "object"}
        grid.info[Object_type.EMPTY] = 8
        grid.info[Object_type.AGENT]= 1
        grid.remove_agent((0,1))
        self.assertEqual(grid.grid[1][0] , Object_type.EMPTY)
        self.assertTrue((0,1) not in grid.agents)
        self.assertEqual(grid.info[Object_type.AGENT], 0)
        self.assertEqual(grid.info[Object_type.EMPTY], 9)




    def test_check_movement(self):
        grid = Grid(3)
        grid.grid[0][0] = Object_type.CAPSULE
        grid.grid[0][1] = Object_type.STRIDER
        grid.grid[1][0] = Object_type.EMPTY
        grid.grid[2][2] = Object_type.EMPTY

        self.assertEqual(grid.check_movement((1,0)), False)
        self.assertEqual(grid.check_movement((0,1)), True)
        self.assertEqual(grid.check_movement((2,2)), True)
        self.assertEqual(grid.check_movement((0,0)), False)
        self.assertEqual(grid.check_movement((-1,-1)), False)
        self.assertEqual(grid.check_movement((3,3)), False)






    def test_publish_movement_action(self):
        grid = Grid(3)
        grid.add_agent((1,1)) 
        agent = grid.agents[(1,1)]
        agent.publish_movement_action(Direction.UP, grid, (1,1))
        agent.publish_movement_action(Direction.RIGHT, grid, (1,1))
        agent.publish_movement_action(Direction.DOWN, grid, (1,1))
        agent.publish_movement_action(Direction.LEFT, grid, (1,1))
        self.assertEqual(grid.action_queue, [((1,1),(1,0),Action_type.MOVE),((1,1),(2,1),Action_type.MOVE),((1,1),(1,2),Action_type.MOVE),((1,1),(0,1),Action_type.MOVE)])
        agent.direction = Direction.RIGHT
        grid.action_queue = []
        agent.publish_movement_action(Direction.UP, grid, (1,1))
        agent.publish_movement_action(Direction.RIGHT, grid, (1,1))
        agent.publish_movement_action(Direction.DOWN, grid, (1,1))
        agent.publish_movement_action(Direction.LEFT, grid, (1,1))
        self.assertEqual(grid.action_queue, [((1,1),(2,1),Action_type.MOVE),((1,1),(1,2),Action_type.MOVE),((1,1),(0,1),Action_type.MOVE),((1,1),(1,0),Action_type.MOVE)])
        agent.direction = Direction.DOWN
        grid.action_queue = []
        agent.publish_movement_action(Direction.UP, grid, (1,1))
        agent.publish_movement_action(Direction.RIGHT, grid, (1,1))
        agent.publish_movement_action(Direction.DOWN, grid, (1,1))
        agent.publish_movement_action(Direction.LEFT, grid, (1,1))
        self.assertEqual(grid.action_queue, [((1,1),(1,2),Action_type.MOVE),((1,1),(0,1),Action_type.MOVE),((1,1),(1,0),Action_type.MOVE),((1,1),(2,1),Action_type.MOVE)])
        agent.direction = Direction.LEFT
        grid.action_queue = []
        agent.publish_movement_action(Direction.UP, grid, (1,1))
        agent.publish_movement_action(Direction.RIGHT, grid, (1,1))
        agent.publish_movement_action(Direction.DOWN, grid, (1,1))
        agent.publish_movement_action(Direction.LEFT, grid, (1,1))
        self.assertEqual(grid.action_queue, [((1,1),(0,1),Action_type.MOVE),((1,1),(1,0),Action_type.MOVE),((1,1),(2,1),Action_type.MOVE),((1,1),(1,2),Action_type.MOVE)])

    def test_apply_direction_offset(self): #sometimes it is fun to be fastidious with test cases
        dummy_brain = {}
        agent = Agent(dummy_brain)
        agent.direction = Direction.UP
        self.assertEqual(agent.apply_direction_offset(Direction.LEFT), Direction.LEFT)
        self.assertEqual(agent.apply_direction_offset(Direction.RIGHT), Direction.RIGHT)
        self.assertEqual(agent.apply_direction_offset(Direction.DOWN), Direction.DOWN)
        self.assertEqual(agent.apply_direction_offset(Direction.UP), Direction.UP)
        agent.direction = Direction.LEFT
        self.assertEqual(agent.apply_direction_offset(Direction.LEFT), Direction.DOWN)
        self.assertEqual(agent.apply_direction_offset(Direction.RIGHT), Direction.UP)
        self.assertEqual(agent.apply_direction_offset(Direction.DOWN), Direction.RIGHT)
        self.assertEqual(agent.apply_direction_offset(Direction.UP), Direction.LEFT)
        agent.direction = Direction.DOWN
        self.assertEqual(agent.apply_direction_offset(Direction.LEFT), Direction.RIGHT)
        self.assertEqual(agent.apply_direction_offset(Direction.RIGHT), Direction.LEFT)
        self.assertEqual(agent.apply_direction_offset(Direction.DOWN), Direction.UP)
        self.assertEqual(agent.apply_direction_offset(Direction.UP), Direction.DOWN)
        agent.direction = Direction.RIGHT
        self.assertEqual(agent.apply_direction_offset(Direction.LEFT), Direction.UP)
        self.assertEqual(agent.apply_direction_offset(Direction.RIGHT), Direction.DOWN)
        self.assertEqual(agent.apply_direction_offset(Direction.DOWN), Direction.LEFT)
        self.assertEqual(agent.apply_direction_offset(Direction.UP), Direction.RIGHT)

    @patch('mega_grid.Agent.apply_direction_offset')
    def test_turn(self, mock_apply_direction_offset):
        dummy_brain = {}
        agent = Agent(dummy_brain)
        agent.direction = Direction.LEFT
        mock_apply_direction_offset.side_effect = [Direction.DOWN]
        agent.turn(Direction.LEFT)
        expected_call_stack = [call.mock_apply_direction_offset(Direction.LEFT)]
        self.assertEqual(agent.direction, Direction.DOWN )
        self.assertEqual(mock_apply_direction_offset.mock_calls, expected_call_stack)
        
    @patch('mega_grid.Grid.check_movement')
    def test_move(self, mock_check_movement):
        mock_check_movement.return_value = True
        grid = Grid(3)
        grid.add_agent((1,1)) 
        agent = grid.agents[(1,1)]
        self.assertTrue( (1,1) in grid.agents.keys() )
        grid.move((1,1),(2,1))
        self.assertEqual(grid.grid[1][2], Object_type.AGENT)
        self.assertEqual(grid.grid[1][1], Object_type.EMPTY)
        self.assertTrue( (1,1) not in grid.agents.keys() )
        self.assertTrue( (2,1) in grid.agents.keys() )
        grid.move((2,1),(0,0))
        self.assertEqual(grid.grid[0][0], Object_type.AGENT)
        self.assertEqual(grid.grid[2][1], Object_type.EMPTY)
        self.assertTrue( (2,1) not in grid.agents.keys() )
        self.assertTrue( (0,0) in grid.agents.keys() )
        mock_check_movement.return_value = False
        grid.move((0,0),(2,2))
        self.assertEqual(grid.grid[0][0], Object_type.AGENT)
        self.assertEqual(grid.grid[2][2], Object_type.EMPTY)
        self.assertTrue( (2,2) not in grid.agents.keys() )
        self.assertTrue( (0,0) in grid.agents.keys() )



if __name__ == '__main__':
    unittest.main()