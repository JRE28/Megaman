#include <iostream>
#include "pugixml.hpp"
#include "../Source/Map.h"
using namespace std;

int main()
{
	Map map("bombman.tmx");
	map.chunkParent = map.doc.child("map").child("layer").child("data");
	map.chunkLoader();
	for(auto i : map.maptxt[0])
	{
		cout << i << " ";
	}
}