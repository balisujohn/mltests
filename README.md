# mltests


Hi all,

This is a project with the loose goal of finding interested ways to generate intelligent agents through trial and error. 
There are currently distinct Python and C++ architectures, each with a default basic spiking neural network and a experimental 
frequency-domain based spiking neural network. This document includes instructions on how to work with each architecture


## C++ architecture



enter the following commands in bash, from the project directory
`
make
chmod +x ./test
cd ./microworld1
make
chmod +x ./microworld1
cd ../microworld2
make
chmod +x ./microworld2
You're good to go!
`
microworlds 1 and 2 can be run from the command line in three modes
`
./microworld1 train
`
runs neuro-evolution from scratch, saving generated toplogy to ./log.txt

`
./microworld1 improve \<file_name\>
`
runs neuro-evolution, starting from an existing topology, and saves to ./log.txt as higher-scoring topologies are found
`
./microworld1 analyze \<file_name\>
`
provides a visualization of the performance of the toplogy specified by the provided file on the microworld task.


## Python architecture
`
python3 ./main.py \<mode\> \<environment\> \<learning_algorithm\> \<file_name\>
`

### modes:

#### train 

runs neuro-evolution from scratch, saving generated toplogy to ./log.txt

#### improve

runs neuro-evolution, starting from an existing topology, and saves to ./log.txt as higher-scoring topologies are found

#### analyze
 
provides a visualization of the performance of the toplogy specified by the provided file on the microworld task.


### environments:

cartpole
chopper
berzerk
xor
biped
pshoppe



##Contact Information

If any of these areas sound interesting to you, don't hesitate to contribute. I can be reached at balisujohn at gmail dot com and other contributors can be reached at their emails if they have provided them.  We are very interested in recieving input and contributions.


Contributors:  
John Balis: balisujohn at gmail dot com  
William Derksen  
Michael Ivanitskiy: mivanits at umich dot edu OR mivanitskiy at hotmail dot com  

Inline dependencies:  
cJSON, courtesy of Dave Gamble and cJSON contributors
