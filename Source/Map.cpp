#include <iostream>
#include <vector>
#include "pugixml.hpp"
#include "Map.h"
using namespace std;

Map::Map(const char* directory)
{
	doc.load_file(directory); //Loads xml in doc (document node)
	chunkParent = doc.child("map").child("layer").child("data").child("chunk"); //Node resembling the parent to all chunk nodes containing map info
	csize = 16; //Chunk width is 16 characters
}

void Map::chunkLoader()
{
	it = 0; //counter to iterate through vector
	string chnk; //Temporary string for convertion
	for(auto i : chunkParent.children("chunk"))
	{
		chnk = i.child_value(); //Way to convert const char* into string 
		tilesets.push_back(vector<string>()); //Pushes new string vector for every new chunk included
		tilesets[it].push_back(chnk); //Pushes chunk into newly created string vector
		it++; //Increments iterator
		
	}
	mapFitter(); //Transforms into maptxt
	unite();
}

void Map::mapFitter()
{
	for(int i = 0; i < tilesets.size();i++)
	{
		stringstream String(tilesets[i][0]);
		string segment; //Provisional string to contain split fragments
		maptxt.push_back(vector<string>());
		while(std::getline(String, segment, ',')) //Separates string when encounters '.'
		{
   			maptxt[i].push_back(segment);
		}
	}
}

void Map::unite()
{
	tilesets.clear();
	cout << tilesets.size();
	for(int count = 0; count < csize; count++)
	{
		tilesets.push_back(vector<string>());
		for(int i = 0; i < maptxt.size(); i++)
		{
			for(int it = 0; it < csize*csize; it++)
			{
				tilesets[count].push_back(maptxt[i][it]);
			}
		}
	}
}

void Map::mapper()
{
	int count = 0;
	int x = 0;
	int y = 0;
	//map position (attributes chunks and maptxt)
	for(auto children : chunkParent.children())
	{
		x = (int) *children.attribute("x").value();
		worldmap.insert(std::pair<int, vector<string>>(x, maptxt[count]))
	}

}