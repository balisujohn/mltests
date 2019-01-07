import json
import random 
import sys
from graph_tool.all import * 
from numpy.random import *

import networkx as netx
from matplotlib import pyplot
from gi.repository import Gtk, Gdk, GdkPixbuf, GObject

from threading import Thread
from time import sleep

#John Balis 2019
#for support email balisujohn@gmail.com


GRAPH_VISUALIZATION_ACTIVE = False
color_map = None
win = None
g = None
figure = None



#deprecated, moving to a graph-tool
def visualize_topology(input):
	edge_labels = {}
	brain = json.loads(input)

	brain_graph = netx.MultiDiGraph()
	#dot = Digraph(comment='brain visualization')

	for neuron_index, neuron in enumerate(brain['neurons']):
		brain_graph.add_node(str(neuron_index))


	for neuron_index, neuron in enumerate(brain['neurons']):
		for target_index, target in enumerate(neuron['targets']):
			brain_graph.add_edge(str(neuron_index),str(neuron['targets'][target_index]), edge_label = neuron['weights'][target_index])
			edge_labels[str(neuron_index),str(neuron['targets'][target_index])] = neuron['weights'][target_index]

	pos = netx.spring_layout(brain_graph, seed = 1)

	pyplot.pause(.0000001)	
	pyplot.clf()
	netx.draw_networkx(brain_graph,pos,edge_labels = edge_labels,with_labels=True,)
	netx.draw_networkx_edge_labels(brain_graph ,pos,edge_labels = edge_labels)
	pyplot.show(block = False)



def render_changes():
	sleep(.0001)
	global win
	win.graph.regenerate_surface()
	win.graph.queue_draw()	
	return True

	

def visualize_brain(input):
	#edge_labels = {}
	brain = json.loads(input)
	#global figure
	global g
	global GRAPH_VISUALIZATION_ACTIVE
	global color_map
	global win

	if not GRAPH_VISUALIZATION_ACTIVE:
		GRAPH_VISUALIZATION_ACTIVE = True
		g = Graph(directed = True)	
		#brain_graph = netx.MultiDiGraph()
		#dot = Digraph(comment='brain visualization')

	
	
		color_map = g.new_vertex_property('string')
	 
		#print('FIRST NEURON ACTIVATION')
		#print(brain['neurons'][0]['fired'])

		for neuron_index, neuron in enumerate(brain['neurons']):
			g.add_vertex()		
			if neuron['fired'] == 1:	
				color_map[g.vertex(neuron_index)] = 'blue'
			else:
				color_map[g.vertex(neuron_index)] = 'gray'


		#brain_graph.node_color =color_map
		#print(color_map)

		for neuron_index, neuron in enumerate(brain['neurons']):
			for target_index, target in enumerate(neuron['targets']):
				g.add_edge(neuron_index,target)
				#edge_labels[str(neuron_index),str(neuron['targets'][target_index])] = neuron['weights'][target_index]

		pos = sfdp_layout(g,K=1)

		win = GraphWindow(g,pos, async = True,  geometry =(500,400) ,vertex_text=g.vertex_index, vertex_font_size=18,vertex_fill_color = color_map)
		cid = GObject.idle_add(render_changes)
		win.connect("delete_event", Gtk.main_quit)
		win.show_all()
		thread = Thread(target = Gtk.main, args = ())
		thread.start()
	else:
		for neuron_index, neuron in enumerate(brain['neurons']):
			if neuron['fired'] == 1:	
				color_map[g.vertex(neuron_index)] = 'blue'
			else:
				color_map[g.vertex(neuron_index)] = 'gray'

#	win = GraphWindow(g, positions, vertex_text=g.vertex_index, vertex_font_size=18, geometry=(200, 200), vertex_fill_color = color_map)
#	win.connect("delete_event", Gtk.main_quit)	
#	win.show_all()
#	win.graph.queue_draw()
	#GRAPH_VISUALIZATION_ACTIVE = True
	#else:
	#	color_map = g.new_vertex_property('string')
	#	for neuron_index, neuron in enumerate(brain['neurons']):		
	#		if neuron['fired'] == 1:	
	#			color_map[g.vertex(neuron_index)] = 'blue'
	#		else:
	#			color_map[g.vertex(neuron_index)] = 'gray'
	#	win.vertex_fill_color = color_map 
	#	win.graph.queue_draw()
		

	#pos = netx.spring_layout(brain_graph, seed = 2048)
	#pyplot.pause(.0000001)	
	#pyplot.clf()
	#netx.draw_networkx(brain_graph,pos,edge_labels = edge_labels,with_labels=True)
	#netx.draw_networkx_edge_labels(brain_graph ,pos,edge_labels = edge_labels)
	#pyplot.show(block = False)

#deprecated, switching to graph-tool
def visualize_activation_state(input):
	edge_labels = {}
	brain = json.loads(input)

	brain_graph = netx.MultiDiGraph()
	#dot = Digraph(comment='brain visualization')


	color_map = []
 
	print('FIRST NEURON ACTIVATION')
	print(brain['neurons'][0]['fired'])

	for neuron_index, neuron in enumerate(brain['neurons']):
		if neuron['fired'] == 1:	
			node_color = 'red'
		else:
			node_color = 'blue'
		brain_graph.add_node(str(neuron_index), color = node_color)

	brain_graph.node_color =color_map
	print(color_map)

	for neuron_index, neuron in enumerate(brain['neurons']):
		for target_index, target in enumerate(neuron['targets']):
			brain_graph.add_edge(str(neuron_index),str(neuron['targets'][target_index]), edge_label = neuron['weights'][target_index])
			edge_labels[str(neuron_index),str(neuron['targets'][target_index])] = neuron['weights'][target_index]

	pos = netx.spring_layout(brain_graph, seed = 2048)
	pyplot.pause(.0000001)	
	pyplot.clf()
	netx.draw_networkx(brain_graph,pos,edge_labels = edge_labels,with_labels=True)
	netx.draw_networkx_edge_labels(brain_graph ,pos,edge_labels = edge_labels)
	pyplot.show(block = False)

