#!/bin/sh


UBUNTU_VERSION="$(lsb_release -c -s)"

if [$UBUNTU_VERSION != "bionic"]; then
	echo "You are using an invalid version of Ubuntu, or something other than UBUNTU, please request a submit a request to the mltests project for a setup script for your operating system, or switch to a recommended ubuntu 18.04 development VM"
	exit;
fi
echo "You are using Bionic Beaver, proceeding with setup"


#python3 setup
apt-get upgrade
apt-get install python3=3.6.7-1~18.04
apt-get install python3-pip=9.0.1-2.3~ubuntu1.18.04.1

#adding graph-tool to the sources list
if grep -q  "deb http://downloads.skewed.de/apt/$UBUNTU_VERSION $UBUNTU_VERSION universe" /etc/apt/sources.list  &&  grep -q  "deb-src http://downloads.skewed.de/apt/$UBUNTU_VERSION $UBUNTU_VERSION universe" /etc/apt/sources.list
then
	echo "graph_tool already added to source list"
else
	cp /etc/apt/sources.list /etc/apt/sources.list.backup
	echo "deb http://downloads.skewed.de/apt/$UBUNTU_VERSION $UBUNTU_VERSION universe" | tee -a /etc/apt/sources.list
	echo "deb-src http://downloads.skewed.de/apt/$UBUNTU_VERSION $UBUNTU_VERSION universe" | tee -a /etc/apt/sources.list
fi
apt-key adv --keyserver keys.openpgp.org --recv-key 612DEFB798507F25

apt-get update
apt-get install python3-graph-tool=2.29-1

pip3 install -U -r ./requirements.txt


