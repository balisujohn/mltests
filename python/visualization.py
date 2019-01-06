import json
import random 
import networkx as netx
from matplotlib import pyplot

#John Balis 2019
#for support email balisujohn@gmail.com


sample = """{
	"neuronCount":	34,
	"neurons":	[{
			"targets":	[33, 1, 0, 21],
			"weights":	[0.615315318107605, 0.93329840898513794, 0.75519257783889771, 0.18334229290485382],
			"threshold":	0.75414222478866577,
			"targetCount":	4
		}, {
			"targets":	[31],
			"weights":	[-1.0231279134750366],
			"threshold":	0.35210898518562317,
			"targetCount":	1
		}, {
			"targets":	[18],
			"weights":	[-0.41195845603942871],
			"threshold":	0.28701755404472351,
			"targetCount":	1
		}, {
			"targets":	[23],
			"weights":	[-0.19674950838088989],
			"threshold":	0.72060739994049072,
			"targetCount":	1
		}, {
			"targets":	[29, 4, 14, 18],
			"weights":	[-0.80874592065811157, 0.85880213975906372, 0.66687560081481934, 0.91382884979248047],
			"threshold":	0.94141888618469238,
			"targetCount":	4
		}, {
			"targets":	[33],
			"weights":	[0.30413687229156494],
			"threshold":	0.94972676038742065,
			"targetCount":	1
		}, {
			"targets":	[19, 17, 31],
			"weights":	[0.26932051777839661, 0.83013588190078735, 0.16129255294799805],
			"threshold":	0.52953535318374634,
			"targetCount":	3
		}, {
			"targets":	[16, 20, 16, 14, 15],
			"weights":	[0.66576999425888062, -0.04563574492931366, -0.10957664251327515, 0.85631012916564941, 0.92618644237518311],
			"threshold":	0.22619657218456268,
			"targetCount":	5
		}, {
			"targets":	[29],
			"weights":	[0.025946389883756638],
			"threshold":	0.24960115551948547,
			"targetCount":	1
		}, {
			"targets":	[15, 27, 29],
			"weights":	[0.82413101196289062, 0.28896588087081909, 0.512537956237793],
			"threshold":	0.73974519968032837,
			"targetCount":	3
		}, {
			"targets":	[4, 32],
			"weights":	[0.71236670017242432, 0.7556835412979126],
			"threshold":	0.88547080755233765,
			"targetCount":	2
		}, {
			"targets":	[21, 17],
			"weights":	[-0.62250602245330811, 0.51386713981628418],
			"threshold":	0.55804699659347534,
			"targetCount":	2
		}, {
			"targets":	[11, 6, 3],
			"weights":	[0.391724556684494, 0.26429510116577148, 0.1367669403553009],
			"threshold":	0.51443660259246826,
			"targetCount":	3
		}, {
			"targets":	[12, 20, 25, 6],
			"weights":	[-0.16974253952503204, 0.25905928015708923, 0.46494966745376587, 0.63338661193847656],
			"threshold":	0.96634423732757568,
			"targetCount":	4
		}, {
			"targets":	[26],
			"weights":	[1.0202827453613281],
			"threshold":	0.25909486413002014,
			"targetCount":	1
		}, {
			"targets":	[18, 21, 26],
			"weights":	[0.088501602411270142, 0.5379149317741394, 0.72591310739517212],
			"threshold":	0.73725044727325439,
			"targetCount":	3
		}, {
			"targets":	[27],
			"weights":	[0.43662762641906738],
			"threshold":	0.13285303115844727,
			"targetCount":	1
		}, {
			"targets":	[12],
			"weights":	[-0.15846812725067139],
			"threshold":	0.98840737342834473,
			"targetCount":	1
		}, {
			"targets":	[7, 14, 30],
			"weights":	[0.033949270844459534, 0.68654501438140869, 0.6862560510635376],
			"threshold":	0.029306467622518539,
			"targetCount":	3
		}, {
			"targets":	[7],
			"weights":	[0.12319934368133545],
			"threshold":	0.55202269554138184,
			"targetCount":	1
		}, {
			"targets":	[26],
			"weights":	[-0.19505852460861206],
			"threshold":	0.98253488540649414,
			"targetCount":	1
		}, {
			"targets":	[],
			"weights":	[],
			"threshold":	0.26526150107383728,
			"targetCount":	0
		}, {
			"targets":	[7],
			"weights":	[-0.54233580827713013],
			"threshold":	0.41967922449111938,
			"targetCount":	1
		}, {
			"targets":	[19, 20, 30, 14, 26],
			"weights":	[0.0049964897334575653, 0.37726059556007385, 0.099220499396324158, 0.12054799497127533, 0.021441411226987839],
			"threshold":	0.41853344440460205,
			"targetCount":	5
		}, {
			"targets":	[27, 25, 18, 15],
			"weights":	[0.13490714132785797, 0.83250331878662109, 0.14768454432487488, 0.966252863407135],
			"threshold":	0.0045265723019838333,
			"targetCount":	4
		}, {
			"targets":	[13, 27],
			"weights":	[-0.699953556060791, 0.66982746124267578],
			"threshold":	0.30256462097167969,
			"targetCount":	2
		}, {
			"targets":	[32, 32, 29, 19],
			"weights":	[-0.69880306720733643, 0.10606127977371216, 0.80843698978424072, 0.11619861423969269],
			"threshold":	0.45656317472457886,
			"targetCount":	4
		}, {
			"targets":	[23, 0, 18],
			"weights":	[0.45826750993728638, 0.383800745010376, 0.46170064806938171],
			"threshold":	0.018423691391944885,
			"targetCount":	3
		}, {
			"targets":	[23],
			"weights":	[0.27649056911468506],
			"threshold":	0.42282959818840027,
			"targetCount":	1
		}, {
			"targets":	[12, 24, 32, 25],
			"weights":	[-0.61623692512512207, 1.0526363849639893, 0.843051552772522, 1.0315709114074707],
			"threshold":	0.18702161312103271,
			"targetCount":	4
		}, {
			"targets":	[31, 16, 30],
			"weights":	[0.6385725736618042, 0.32149600982666016, 0.35162314772605896],
			"threshold":	0.649017333984375,
			"targetCount":	3
		}, {
			"targets":	[13, 4],
			"weights":	[-0.58940917253494263, 0.13425324857234955],
			"threshold":	0.69516152143478394,
			"targetCount":	2
		}, {
			"targets":	[],
			"weights":	[],
			"threshold":	0.47562715411186218,
			"targetCount":	0
		}, {
			"targets":	[28, 25, 29, 31],
			"weights":	[0.96664702892303467, 0.75614720582962036, 0.53594177961349487, 0.39908754825592041],
			"threshold":	0.18467336893081665,
			"targetCount":	4
		}]
}
"""




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



def visualize_activation_state(input):
	edge_labels = {}
	brain = json.loads(input)

	brain_graph = netx.MultiDiGraph()
	#dot = Digraph(comment='brain visualization')


	color_map = []

	for neuron_index, neuron in enumerate(brain['neurons']):
		if neuron['fired'] == 1:	
			color_map.append('red')
		else:
			color_map.append('blue')
		brain_graph.add_node(str(neuron_index))


	for neuron_index, neuron in enumerate(brain['neurons']):
		for target_index, target in enumerate(neuron['targets']):
			brain_graph.add_edge(str(neuron_index),str(neuron['targets'][target_index]), edge_label = neuron['weights'][target_index])
			edge_labels[str(neuron_index),str(neuron['targets'][target_index])] = neuron['weights'][target_index]

	pos = netx.spring_layout(brain_graph, seed = 2048)
	pyplot.pause(.0000001)	
	pyplot.clf()
	netx.draw_networkx(brain_graph,pos,edge_labels = edge_labels,with_labels=True,node_color = color_map)
	netx.draw_networkx_edge_labels(brain_graph ,pos,edge_labels = edge_labels)
	pyplot.show(block = False)
