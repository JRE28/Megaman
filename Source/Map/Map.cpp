#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "pugixml.hpp"
#include "Map.h"
using namespace std;

Map::Map(const char* directory, int xtiles, int ytiles)
{
	doc.load_file(directory); //Loads xml in doc (document node)
	chunkParent = doc.child("map").child("layer").child("data").child("chunk"); //Node resembling the parent to all chunk nodes containing map info
	tsize = sf::Vector2i(16,16);
	tilecount = sf::Vector2i(xtiles, ytiles);
	firstrun = true;
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
	mapper();
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

void Map::mapper()
{
	int count = 0;
	int x;
	int y;
	//map position (attributes chunks and maptxt)
	for(auto children : chunkParent.children())
	{
		x = atoi(children.attribute("x").value()); //Getting x and y values from chunk element in xml
		y = atoi(children.attribute("y").value());
		xattr.push_back(x); //Pushes x values into vector to compair after loop
		yattr.push_back(y); //Pushes y
		worldmap.insert(std::make_pair(x, std::map<int, vector<string>>())); //Creating 2d map, to identify chunks of map with x and y 
		worldmap[x].insert(make_pair(y, maptxt[count]));
		count++;
	}
	
	upleft = sf::Vector2i(*min_element(xattr.begin(), xattr.end()), *min_element(yattr.begin(), yattr.end())); //Most upleft position (lowest Y)
	downright = sf::Vector2i(*max_element(xattr.begin(), xattr.end()), *max_element(yattr.begin(), yattr.end())); //Most downright position (highest Y)

}

bool Map::setTexture(string directory)
{
	if(tileset.loadFromFile(directory))
	{
		tiles.x = tileset.getSize().x / tsize.x;						
		tiles.y = tileset.getSize().y/ tsize.y;
		this->tile.setTexture(tileset);
		return true;
	}
	return false;
}

void Map::setTileWidth(int width, int height)
{
	tsize = sf::Vector2i(width, height); //Sets new size
}


TILE Map::selectTile(int no)
{
	TILE tl;
	if(no != 0)
	{
		no--;
		int x = no % tiles.x;
		int y = no / tiles.x;
		tl.sprite.setTexture(tileset);
		tl.sprite.setTextureRect(sf::IntRect(tsize.x* x, tsize.y* y, tsize.x, tsize.y));		//Problem is output 'no' from createSprite is correct, but when in loop, each tile has 
	}																							//a different no than the one before
	tl.no = no;
	return tl;
}

void Map::createSprite(int no)  //Input consists of number corresponding to tile in tileset
{
	TILE sp;
	sp = selectTile(no);
	//cout << sp.no << " ";
	sprites.push_back(sp);
	//cout << sp.no << " ";

}


/*void Map::drawMap(sf::RenderWindow &window, int offset)
{
	int count = 0;
	for(int y  = downleft.y; y <= upright.y; y+=16)
	{
		for(int i = downleft.x; i <= upright.x; i+=16)
		{
			count = 0;
			for(string el : worldmap[i][y])
			{	
				if(firstrun)
				{
					createSprite(stoi(el));	
					//cout << offset << " ";
					cout << (i + count)*tsize.x << " " << ((y)*tsize.y) << " ";
					sprites[count].sprite.setPosition((i + count)*tsize.x, ((y)*tsize.y)+offset);  //Sets tile position in map
				}
				window.draw(sprites[count].sprite);
				count++;
			}
		}
	}
	firstrun = false;
}
*/

void Map::drawMap(sf::RenderWindow &window, int screenYsize)
{
	//Negative Y coordinates problem solving -> Upright is the one with lowest y
	//Reasemble drawmap func, as y remains the same during for
	int count = 0;
	int blockrow = 0; //Represents the number of the row a tile is in
	int blockcolumn = 0;
	for(int y = upleft.y; y <= downright.y; y+=16)
	{
		//cout << downright.x << " " << downright.y;
		for(int x = upleft.x; x <= downright.x; x+=16)
		{
			count = 0;
			blockrow = 0;
			blockcolumn = 0;
			for(string tile : worldmap[x][y])
			{
				if(count%16 == 0)
				{
					blockrow++;
					blockcolumn = 0;
				}
				else
				{
					blockcolumn++;
				}
				if(firstrun)
				{
					TILE tl;
					//cout << stoi(tile) << " ";
					sprites[count] = NULL;
					//cout << sprites[count].no << " ";
					sprites[count] = selectTile(stoi(tile));
					//cout << tl.no << " ";
					//createSprite(stoi(tile));
					//cout << sprites.size() << " ";
					sprites[count].sprite.setPosition((x*tsize.x)+(blockcolumn*tsize.x), y + (blockrow*tsize.y) + screenYsize);
					//cout << count*tsize.x;
					cout << (x*tsize.x)+(blockcolumn*tsize.x) << " " << y + (blockrow*tsize.y) + screenYsize << " ";
					//cout << firstrun << " ";
				}
				
				window.draw(sprites[count].sprite);
				//cout << sprites.size() << " ";
				count++;
			}
		}
	}
	firstrun = false;
}
