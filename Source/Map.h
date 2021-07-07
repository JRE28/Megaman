#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <pugixml.hpp>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

class Map
{
public:
	Map(const char* directory); //Loads xml in constructor
	void chunkLoader(); //Loads chunks into tileset multivector
	void mapper(); //Maps maptxt with position in world
	pugi::xml_document doc; //Document node (root)
	// pugi::xml_parse_result result; 
	pugi::xml_node chunkParent; //Chunk nodes parent
	vector<vector<string>> tilesets; //Multidimensional vector to hold map
	vector<vector<string>> maptxt; //Real 2d representation of map
	std::map<int, vector<string>> worldmap;
private:
	void mapFitter(); //(chunkLoader) Transforms tilesets vector into full 2d map: maptxt
	void unite(); //Unite all maptxt subarrays in 
	unsigned int it; //Number of chunks, registered to make corresponding vectors
	int csize; //Width, and height of chunk 
	pugi::xml_attribute x, y;
};

#endif

