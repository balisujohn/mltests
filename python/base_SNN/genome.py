from random import uniform 
from random import randrange



class Node_gene():
	def __init__(self):
		self.type
		self.innovation_number
		self.enabled 
		self.threshold

class Edge_gene():
	 def __init__(self):
		self.pre_syn
		self.post_syn
		self.weight
		
		self.innovation_number
		self.enabled 


class Genome():

	def __init__(self):
		self.innovation_counter = 0
		self.node_genes = []
		self.edge_genes = []




	def node_mutation(self);
		new_node = Node_gene()
		new_node.innovatio_number = self.innovation)counter
		new_node.enabled = True
		new_node.threshold = uniform(0,1)
		new_node.type = #TODO
		self.innovation_counter+=1
		


	def edge_mutation(self)
		assert(len(self.node_genes)>1) ## ensures there are at least two nodes to form edges between 
		new_edge = Edge_gene()
		new_edge.pre_syn = randrange(len(self.node_genes))
		new_edge.post_syn = randrange(len(self.node_genes))
		while new_edge.post_syn == new_edge.pre_syn:	
			new_edge.post_syn = randrange(len(self.node_genes))
		new_edge.weight = uniform(0,1)
		new_edge.innovation_number = self.innovation_counter


		self.innovation_counter += 1	
	

	def construct_brain(self):
		



def genome_crossover(genome_1, genome_2):
	
		
