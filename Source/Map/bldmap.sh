#!/bin/bash
cd ~/Megaman/Source/Map
g++ -c *.cpp


g++ *.o -o map.exe -lsfml-graphics -lsfml-window -lsfml-system -pthread 
./map.exe	

