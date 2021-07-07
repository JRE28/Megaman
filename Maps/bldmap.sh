#!/bin/bash
cd ~/Megaman/Maps/
g++ -c *.cpp

g++ -c ../Source/Map.cpp

g++ *.o -o map.exe -lsfml-graphics -lsfml-window -lsfml-system -pthread 
./map.exe	

