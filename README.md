#
mltests

## About

Hi all,

This is a project with the loose goal of finding interesting ways to generate intelligent agents through trial and error. 
There are currently distinct Python and C++ architectures, each with a default basic spiking neural network and a experimental 
frequency-domain based spiking neural network. This document includes instructions on how to work with each architecture. The docker development environment is intended for use with the python architecture. Here is a showcase video, showing the behavior of some of the topologies stored in this repository: 
https://www.youtube.com/watch?v=zFZZjQkz7RA

## Building dev Docker image
To set up the mltests dev environment with Docker, run the following commands in bash:
````
cd mltests
docker build -t mltests-dev .
````

Vim is included by default, feel free to add your own editor to the Dockerfile to suit your own preferences. In GUI mode, you can use visual editors! Git is included by default, so you can use git directly with your own fork of the mltests project from inside the Docker container.

### Running dev Docker image with GUI(Recommended)
````
xhost +SI:localuser:root
docker run --rm \
            -e DISPLAY=$DISPLAY \
            -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
            --ipc=host \
            --user 0:0 \
            --cap-drop=ALL \
            --security-opt=no-new-privileges \
	    -it \
            mltests-dev

````
Adapted from https://github.com/mviereck/x11docker/wiki/Short-setups-to-provide-X-display-to-container.

Please note that this breaks container isolation!

### Running dev Docker image without GUI:
````
docker run -it --user 0:0  mltests-dev
````

## Python architecture
```
cd python_neuro_ev
python3 ./main.py <mode> <environment> <learning_algorithm> <file_name>
```

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
sologrid




## C++ architecture
enter the following commands in bash, from the project directory
```
make
chmod +x ./test
cd ./microworld1
make
chmod +x ./microworld1
cd ../microworld2
make
chmod +x ./microworld2
You're good to go!
```
microworlds 1 and 2 can be run from the command line in three modes
```
./microworld1 train
```
runs neuro-evolution from scratch, saving generated toplogy to ./log.txt

```
./microworld1 improve <file_name>
```
runs neuro-evolution, starting from an existing topology, and saves to ./log.txt as higher-scoring topologies are found
```
./microworld1 analyze <file_name>
```
provides a visualization of the performance of the toplogy specified by the provided file on the microworld task.



#### analyze
 
provides a visualization of the performance of the toplogy specified by the provided file on the microworld task.





## Contact Information

If any of these areas sound interesting to you, don't hesitate to contribute. I can be reached at balisujohn at gmail dot com and other contributors can be reached at their emails if they have provided them.  We are very interested in recieving input and contributions.


Contributors:  
John Balis: balisujohn at gmail dot com  
William Derksen  
Michael Ivanitskiy: mivanits at umich dot edu OR mivanitskiy at hotmail dot com  

Inline dependencies:  
cJSON, courtesy of Dave Gamble and cJSON contributors
