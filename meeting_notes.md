# Meeting 1: Dec 22 2018

## discussed usage of tensor product:
* chemical signalling localization
* generation of basic structure

## frequency domain signalling:
* frequency pulse object:
    * frequency 
      * might be possible to store frequency implicit in array position, but this is likely inefficient
    * amplitude
    * phase shift
    * num pulses (?)
* neuron stores two data structures of pulse input (variable length arrays?) to describe full waveform
    * one arr as sum of inputs
    * other arr as result of activation function (might not need to be explicitly stored, just passed to neurons along axon)
    * activation function needs to both compress and process frequency domain input
      * particular care needs to be taken in cases when input period approaches min recovery time

## short term goals/tasks:
* (DONE) get MLtests code working in C++
* (in progress) basic array-based frequency implementation in MLtests code
  * decide on optimal data structure for storing pulses in a neuron
* study Hodkin-Huxley or other models to determine activation/compression function, particularly how it acts on high frequencies
  * use this to implement a more accurate frequency domain architecture
* possible optimizations of only firing neurons with changed waveform
  * put neurons into a queue when they need to be fired?
  * run tests on this. if the proportion of neurons in the queue out of total neurons is close to 1, then this optimization is unneccesary
  * if we use this optimization, need to figure out how to update target waveform without taking all sources
    * could subtract previous step action potential from target, and replace new action potention
    * could find diff between new and old action potential, and add that to target 
    * both assume linear, might not play nice with waveform compression
* double check pendulum physics
* extension of tensor product

## longer term goals:
* explore applications of chemical signalling in ANN systems, particularly for novel learning methods
	* tensor products can be used to localize neurotransmitter concentrations
* further explore and optimize frequency-domain architecture

all papers can be found at 

https://www.dropbox.com/sh/yxabj0q5s66skqe/AAAVT3FYVivLd4GxX9o_Ypema?dl=0

# Meeting 2: Jan 6 2019

## cartpole solved!
* a network trained using the python architecture was able to solve the openAI cartpole instance!
## frequency-tensor brain
* started work on frequency-tensor architecture in python

# Meeting 3: Jan 18 2019

## Introduction
* onboard new members if present
## setting up neuro-evolution ssh server(s)
* Ann Arbor
* Madison
## current state of python implementation
* Results
* work on neat implementation
## tensor-product architecture
* c++ implementation












