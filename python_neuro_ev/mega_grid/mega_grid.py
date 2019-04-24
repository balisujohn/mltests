
import numpy as np
import copy
import sys

SECTOR_SIZE = 10
SECTOR_COUNT = 2

SYM_EMPTY = 0
SYM_AGENT = 1
SYM_STRIDER = 2
SYM_CAPSULE = 3


baseline_densities = {SYM_AGENT : .05, SYM_STRIDER: .01 , SYM_CAPSULE : .25}
degen_enabled = {SYM_AGENT : False, SYM_STRIDER: False , SYM_CAPSULE : True}

def norm_dict(data):
	scaling = sum(data.values())
	for key in data:
		data[key] /= scaling
	

def create_sector():
	info = {SYM_EMPTY : 0, SYM_AGENT: 0, SYM_CAPSULE : 0, SYM_STRIDER : 0} # 
	sector_shape = (SECTOR_SIZE, SECTOR_SIZE)
	return info, np.zeros(sector_shape)


def transform_cell(info,curr_sym):
	if curr_sym == SYM_EMPTY:
		densities = dict([(key, info[key]/ SECTOR_SIZE ** SECTOR_SIZE) for key in info])
		offsets = dict([(key,baseline_densities[key] - info[key]) for key in baseline_densities])	
		norm_dict(offsets)
		print(offsets)


def passive_physics(info, sector):
	old_info = copy.deepcopy(info)
	for i in range(len(sector)):
		for c in range(len(sector[0])):
				sym = transform_cell(old_info,sector[i][c])
				sector[i][c] = sym
				info[sym] += 1
				sys.exit(1)
	



#phases of a world-frame
#passive physics phase:
#spontaneous generation/degeneration based on sector-wide stats

#physics/agent pass
# physics objects and agent updates

(info, sector) = create_sector()
info = passive_physics(info,sector)






