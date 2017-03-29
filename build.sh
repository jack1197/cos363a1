#!/bin/bash
rm -rf ./Bin
mkdir Bin
g++ -o ./Bin/project */*.cpp -std=c++11 -lm -lGL -lGLU -lglut
find . -type f | grep ".tga" | xargs -I file cp file ./Bin/
find . -type f | grep ".obj" | xargs -I file cp file ./Bin/
