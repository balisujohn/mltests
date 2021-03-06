FROM ubuntu:18.04

ENV DEBIAN_FRONTEND=noninteractive




#python3 setup
RUN apt-get update
RUN apt-get --yes install dialog
RUN apt-get --yes install apt-utils
RUN apt-get --yes install vim 
RUN apt-get --yes upgrade
RUN apt-get --yes install python3 
#=3.6.7-1~18.04
RUN apt-get --yes install python3-pip
RUN apt-get --yes install python-opengl
#=9.0.1-2.3~ubuntu1.18.04.1



#installing and configuring vscodium
#this alias is used to force codium to run as a root user
RUN echo 'alias codium="codium --user-data-dir=\\"/.vscodium-root\\""' >> ~/.bashrc
RUN . ~/.bashrc
RUN apt-get --yes install libasound2
RUN apt-get --yes install software-properties-common 
RUN apt-get --yes install wget
RUN wget -qO - https://gitlab.com/paulcarroty/vscodium-deb-rpm-repo/raw/master/pub.gpg | apt-key add -
RUN apt-add-repository 'deb https://gitlab.com/paulcarroty/vscodium-deb-rpm-repo/raw/repos/debs/ vscodium main' 
RUN apt-get update
RUN apt-get --yes install codium 

#adding graph-tool to the sources list

RUN cp /etc/apt/sources.list /etc/apt/sources.list.backup
RUN echo "deb http://downloads.skewed.de/apt/bionic bionic universe" | tee -a /etc/apt/sources.list
RUN echo "deb-src http://downloads.skewed.de/apt/bionic bionic universe" | tee -a /etc/apt/sources.list


#verifying the security of graph-tool
RUN apt-key adv --keyserver keys.openpgp.org --recv-key 612DEFB798507F25

#installing graph-tool
RUN apt-get update
RUN apt-get  --yes install python3-graph-tool


# installing git and cloning the project repo
RUN apt-get --yes install git
#WORKDIR /home
RUN git clone https://github.com/balisujohn/mltests.git
WORKDIR /mltests
RUN git fetch --all



#updating our python environment to match the requirements file
RUN pip3 install -U -r ./python_neuro_ev/requirements.txt

