import json
import sys
from graph_tool.all import * 
from numpy.random import *

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


def render_changes():
	sleep(.0001)
	global win
	win.graph.regenerate_surface()
	win.graph.queue_draw()	
	return True

	

def visualize_brain(input): ## visualizing a brain with fixed topology for the visualization session
	brain = json.loads(input)

	global g
	global GRAPH_VISUALIZATION_ACTIVE
	global color_map
	global win

	if not GRAPH_VISUALIZATION_ACTIVE:
		GRAPH_VISUALIZATION_ACTIVE = True
		g = Graph(directed = True)	
		
	
		color_map = g.new_vertex_property('string')
	 

		for neuron_index, neuron in enumerate(brain['neurons']):
			g.add_vertex()		
			if neuron['fired'] == 1:	
				color_map[g.vertex(neuron_index)] = 'blue'
			else:
				color_map[g.vertex(neuron_index)] = 'gray'

		for neuron_index, neuron in enumerate(brain['neurons']):
			for target_index, target in enumerate(neuron['targets']):
				g.add_edge(neuron_index,target)

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


