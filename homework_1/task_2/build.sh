#!/usr/bin/env bash

echo "Task 1: Build the ipb_arithemetic library Toan dai ca"

rm -rf build
mkdir build

c++ -c -I./include src/subtract.cpp -o build/subtract.o
c++ -I ./include -c src/sum.cpp -o  build/sum.o

ar rcs build/libipb_arithmetic.a build/subtract.o build/sum.o 

c++ src/main.cpp -I ./include -L ./build -lipb_arithmetic -o ./results/bin/main

echo "Finished compiling!!!!"
echo "Running main.cpp"

./results/bin/main
