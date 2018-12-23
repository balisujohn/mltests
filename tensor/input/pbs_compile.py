import sys
import os

# template of pbs script

print "loading templates..."

pbs_template_file = open( 'pbs_template.txt', 'r' )
PBS_TEMPLATE = pbs_template_file.read()

# template of consts.h
consts_template_file = open( 'consts_template.txt', 'r' )
CONSTS_TEMPLATE = consts_template_file.read()

print "templates loaded!\n"

# get start and end n
print "please input range of n to create files for"
start_n = int(raw_input('start n: '))
end_n = int(raw_input('end n: '))

# loop through all n, creating files and compiling code
for loop_n in range(start_n, end_n + 1):
	print "===" * 10
	print "\nfor n = " + str(loop_n)

	print "editing consts.h file"

	# edit "consts.h"
	context_consts = { "loop_n" : loop_n }

	constsfile = open('consts.h','w+')
	constsfile.write(CONSTS_TEMPLATE.format(**context_consts))
	constsfile.close()

	print "compiling consts.h"

	# compile with modified "consts.h"
	os.system('g++ -O3 -std=c++11 "gen_dice_byID.cpp" -o "program/gendice_' + str(loop_n) + '.exe" ')

	print "creating pbs script"

	# creats pbs script
	str_pbsfilename = 'program/job_gendice_' + str(loop_n) + '.pbs'

	# estimate walltime and memory requirements
	# RAM in MB
	req_mem = 5000
	# time in hours
	req_walltime = 1

	# create context dictionary
	context_pbs = {
	"loop_n" : loop_n,
	"memory" : req_mem,
	"hrs_walltime" : req_walltime
	}

	pbsfile = open(str_pbsfilename, 'w+')
	pbsfile.write(PBS_TEMPLATE.format(**context_pbs))
	pbsfile.close()

	print "done for n = " + str(loop_n)
