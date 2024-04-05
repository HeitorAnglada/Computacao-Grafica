#!/usr/bin/env bash
# g++ -std=c++17 ./src/main.cpp -o main ./src/glad.c -I./include -lGL -lSDL2 -ldl && ./main
g++ ./src/main.cpp -o main ./src/glad.c -I./include -lGL -lSDL2 -ldl && ./main