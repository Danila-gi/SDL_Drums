#!/bin/bash

if [ -d "build" ]; then
    rm -rf build
fi

mkdir build
cp -r fonts/ build/
cd build
cmake .. && make
./game