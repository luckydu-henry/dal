#!/bin/bash

sudo apt install libopenal-dev
sudo apt install libsndfile-dev
sudo apt install gcc
sudo apt install make

mkdir build
cd build
cmake ..
make
