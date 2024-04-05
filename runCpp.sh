#!/usr/bin/env bash
# g++ -std=c++20 ./src/*.cpp -o main ./src/glad.c -I./include -lGL -lSDL2 -ldl && ./main
g++ ./src/*.cpp -o main ./src/glad.c -I./include -lGL -lSDL2 -ldl && ./main