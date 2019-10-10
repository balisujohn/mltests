
import sys
import os
sys.path.insert(0,".")
sys.path.insert(0,"./base_SNN")
import numpy as np
import copy
from random import uniform,shuffle
from enum import IntEnum, Enum
from utils import clear
import pprint
import brain
import utils 

def init_mega_grid_params():
	brain.Mutation_params.set_mutation_to_default_1(brain.Mutation_params)
	brain.Mutation_params.neuron_start_count = 10
	brain.Mutation_params.input_count = 3
	brain.Mutation_params.reflex_pair_prob = .40
	brain.Mutation_params.mutation_cycles = 5
	brain.Mutation_params.output_count = 3
	brain.Mutation_params.upper_input_bounds = [.0000001] * 3
	brain.Mutation_params.lower_input_bounds = [-.0000001] * 3




class Object_type(IntEnum):
	EMPTY = 0
	AGENT = 1
	STRIDER = 2
	CAPSULE = 3



# enum for direction, we're going to be a bit hacky with this and actually use the integer to make cycling through directions easier
class Direction(IntEnum):
	UP = 0
	RIGHT = 1
	DOWN = 2
	LEFT = 3


class Action_type (IntEnum):
	PASS = 0
	MOVE = 1
	INTERACT = 2

#Flags to determine visualization and learning mode DEPRECATED TODO REFACTOR
class Learning_flags(Enum):
	VISUALIZATION_ON = 1
	VISUALIZATION_OFF = 2




class Grid():

	object_colors = {Object_type.AGENT: (1,0,0), Object_type.STRIDER: (0,1,0), Object_type.CAPSULE: (0,0,1)}

	def __init__(self, sector_size):
		self.info = {Object_type.AGENT : 0, Object_type.EMPTY: sector_size * sector_size, Object_type.CAPSULE : 0, Object_type.STRIDER : 0} 
		sector_shape = (sector_size, sector_size)
		self.grid = np.zeros(sector_shape)
		self.agents = {}
		self.action_queue = []
		# for objects which may experience spontaneous generation and degeneration, these numbers
		# describe as a percent the percent of occupied space generation and degeneration will trend 
		# towards for each item. 
		self.baseline_densities = { Object_type.EMPTY : .74, Object_type.STRIDER: .01 , Object_type.CAPSULE : .25}
		# specifies whether spontaneous degeneration is enabled for items.
		self.degen_enabled = {Object_type.AGENT : False, Object_type.STRIDER: True , Object_type.CAPSULE : True ,Object_type.EMPTY : True}
		self.sector_size = sector_size


	def visualize_grid(self):
		for i in range(self.sector_size):
			for c in range(self.sector_size):
				print(int(self.grid[i][c]), end = "")
			print()

	def visualize_detailed_grid(self):
		for i in range(self.sector_size):
			for c in range(self.sector_size):
				if self.grid[i][c] == int(Object_type.AGENT):
					if self.agents[(c,i)].direction == Direction.UP:
						print('^' , end = "")
					if self.agents[(c,i)].direction == Direction.RIGHT:
						print('>' , end = "")
					if self.agents[(c,i)].direction == Direction.DOWN:
						print('v' , end = "")
					if self.agents[(c,i)].direction == Direction.LEFT:
						print('<' , end = "")
				else:
					print(int(self.grid[i][c]), end = "")
			print()


	def add_agent(self, coords): #todo add new brain 
		if self.grid[coords[1]][coords[0]] != int(Object_type.AGENT):
			self.info[Object_type.AGENT] += 1
		self.grid[coords[1]][coords[0]] = int(Object_type.AGENT)
		brain_instance = brain.Brain()
		self.agents[coords] = Agent(brain_instance)

	def check_movement(self, coords):
		for coord in coords:
			if coord < 0 or coord >= self.sector_size:
				return False
		if Object_type(self.grid[coords[1]][coords[0]]) != Object_type.EMPTY:
			return False
		return True

	def move(self, start, dest):
		if Object_type(self.grid[dest[1]][dest[0]]) == Object_type.EMPTY:
			self.grid[dest[1]][dest[0]] = self.grid[start[1]][start[0]]
			self.grid[start[1]][start[0]] = int(Object_type.EMPTY)



	###
	# ray tracing in a 2 dimensional discrete grid to determine the value of a single pixel sensor
	# for now we are forgoing depth perception
	###
	def sense(self, coordinates, direction): 
		x_coord = coordinates[0] 
		y_coord = coordinates[1]

		if direction == Direction.UP:
			while y_coord > 0:
				y_coord -= 1
				if self.grid[y_coord][x_coord] != int(Object_type.EMPTY):
					return self.object_colors[Object_type(self.grid[y_coord][x_coord])]

		elif direction == Direction.LEFT:
			while x_coord > 0:
				x_coord -= 1
				if self.grid[y_coord][x_coord] != int(Object_type.EMPTY):
					return self.object_colors[Object_type(self.grid[y_coord][x_coord])]

		elif direction == Direction.RIGHT:
			while x_coord < self.sector_size-1:
				x_coord += 1
				if self.grid[y_coord][x_coord] != int(Object_type.EMPTY):
					return self.object_colors[Object_type(self.grid[y_coord][x_coord])]

		elif direction == Direction.DOWN:
			while y_coord < self.sector_size-1:
				y_coord += 1
				if self.grid[y_coord][x_coord] != int(Object_type.EMPTY):
					return self.object_colors[Object_type(self.grid[y_coord][x_coord])]

		return (0,0,0)

	def norm_dict(self, value_dict):
		result = copy.deepcopy(value_dict)
		val_sum = sum(result.values())
		for key in value_dict:
			result[key] = result[key]/float(val_sum) 
		return result


	def passive_cell_update(self, curr_sym, offsets, baseline_densities):
		#print([value for key,value in offsets.items()])
		# the probability of any sort of generation or degeneration occuring is equal to the current offset from baseline densities
		#divided by the total possible offset form baseline densities. 
	#	print("offsets")
		#print(offsets)
		#print(offsets.values())
		if (uniform(0,1) < sum ([abs(value) for value in offsets.values()]) / len(list(baseline_densities.values()))) and self.degen_enabled[Object_type(curr_sym)]:
			selector = uniform(0,1)
			total_prob = 0.0
			offsets = self.norm_dict(offsets)
			for key, value in offsets.items():
				total_prob += value
				if total_prob  >= selector:
					return key
				

		return curr_sym

	def passive_physics(self):
		old_info = copy.deepcopy(self.info)
		densities = dict([(key, old_info[key]/ (self.sector_size * self.sector_size)) for key in old_info])
		offsets = dict([(key,abs(self.baseline_densities[key] - densities[key])) for key in self.baseline_densities])	
		for i in range(self.sector_size):
			for c in range(self.sector_size):
				sym = self.passive_cell_update(self.grid[i][c],offsets, self.baseline_densities)
				if int(sym) != self.grid[i][c]:
					self.info[Object_type(self.grid[i][c])] -= 1
					self.info[sym] += 1
					self.grid[i][c] = int(sym)


	def advance_agents(self):
		## get randomly ordered list of agents, sense, run, harvest actuation and publish to action_queue
		agent_keys = list(self.agents.keys())
		shuffle(agent_keys)
		for key in agent_keys: #useful to note here that each 'key' is a tuple containing agent location in (x,y) format
			agent = self.agents[key]
			agent.energy -= 1
			#sense
			observations = self.sense(key, agent.direction)
			output = []
			for i in range(len(observations)): ## setting our bounds appropriately for threshold mutations
				brain.Mutation_params().upper_input_bounds[i] = max(brain.Mutation_params().upper_input_bounds[i],observations[i])
				brain.Mutation_params().lower_input_bounds[i] = min(brain.Mutation_params().lower_input_bounds[i],observations[i])


			print(observations)
			result = agent.brain.advance_n_with_mode(observations, 3, 10, utils.Visualization_flags.VISUALIZATION_ON)
			print(result)
			numerical_result = utils.binary_array_to_decimal(result)
			print(numerical_result)
			agent.generate_action(numerical_result, self.grid, key)

			
	def active_physics(self):
		for action in self.action_queue:
			if (action[2] == Action_type.MOVE):
				self.move(action[0], action[1])



			#public to action_queue
				

class Agent():
	def __init__(self, brain):
		self.brain = brain
		self.direction = Direction.UP
		self.energy = 20
	
	## sensing calculate sensory data
	## evaluation decide on action
	## active physics(actuation phase)

	def apply_direction_offset(self, direction):
		offset = int(direction)
		return Direction((self.direction + offset) % 4)

	def mutate(self):
		self.brain.default_mutation(3,3)

	###
	# moves the agent if there is no physical obstruction in the world, updating both the the agent's and the world's info for the new frame of time. 
	###
	def publish_movement_action(self , relative_direction, grid, coords):
		move_direction = self.apply_direction_offset(relative_direction)
		if move_direction == Direction.UP:
			new_coords = (coords[0], coords[1]-1)
			grid.action_queue.append((coords, new_coords , Action_type.MOVE))
		elif move_direction == Direction.RIGHT:
			new_coords = (coords[0]+1, coords[1])
			grid.action_queue.append((coords, new_coords,Action_type.MOVE))
		elif move_direction == Direction.DOWN:
			new_coords = (coords[0], coords[1]+1)
			grid.action_queue.append((coords, new_coords,Action_type.MOVE))
		elif move_direction == Direction.LEFT:
			new_coords = (coords[0]-1, coords[1])
			grid.action_queue.append((coords, new_coords,Action_type.MOVE))
		


		##
		# should only be called with Direction.LEFT or Direction.RIGHT
		##
	def turn(self, turn_direction):
		self.direction = self.apply_direction_offset(turn_direction)

	
	def generate_action(self, selection, grid, coords):
		if selection == 0:
			pass ## no action
		elif selection == 1:
			self.turn(Direction.LEFT)
		elif selection == 2:
			self.turn(Direction.RIGHT)
		elif selection == 3:
			self.publish_movement_action(Direction.UP, self, coords)
		elif selection == 4:
			self.publish_movement_action(Direction.RIGHT, self, coords)
		elif selection == 5:
			self.publish_movement_action(Direction.DOWN, self, coords)
		elif selection == 6:
			self.publish_movement_action(Direction.LEFT, self, coords)
		elif selection == 7:
			pass #interact


#phases of a world-frame
#passive physics phase:
#spontaneous generation/degeneration based on sector-wide stats

#physics/agent pass
# physics objects and agent updates
if __name__ == '__main__':
	init_mega_grid_params()
	grid = Grid(20)
	grid.add_agent((1,1))
	grid.agents[(1,1)].mutate()


	for i in range(999999999):
		grid.passive_physics()
		grid.advance_agents()
		grid.active_physics()
		grid.visualize_detailed_grid()
		pprint.pprint(grid.info)
		clear(1)




