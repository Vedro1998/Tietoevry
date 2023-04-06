#!/bin/bash

# out-of-source build
rm -r ./build
mkdir ./build

cd ./build
cmake ../
make
