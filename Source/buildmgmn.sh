#!/bin/bash
cd ~/Megaman/Source/
g++ -c Anim.cpp
g++ -c Megaman.cpp
g++ -c main.cpp
g++ -c Mworld.cpp
g++ Megaman.o main.o Anim.o Mworld.o -o Megaman.exe -lsfml-graphics -lsfml-window -lsfml-system -pthread
./Megaman.exe	

