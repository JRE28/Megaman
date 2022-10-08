#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <pugixml.hpp>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

struct TILE
{
	sf::Sprite sprite; //Sprite with tile texture 
	unsigned int no; //Number of tile in tileset
};

class Map
{
public:
	Map(const char* directory, int xtiles, int ytiles); //Loads xml in constructor
	void chunkLoader(); //Loads chunks into tileset multivector
	void mapper(); //Maps maptxt with position in world
	void drawMap(sf::RenderWindow &window, int screenYsize); //Draws map in screen; offset represents height of screen, or vertical lowerage of map drawing
	void setTileWidth(int width, int height); //Sets new tile width/height
	bool setTexture(string tdirectory); //Loads texture
	string tdirectory; //Directory of tileset image
	pugi::xml_document doc; //Document node (root)
	// pugi::xml_parse_result result; 
	pugi::xml_node chunkParent; //Chunk nodes parent
	vector<vector<string>> tilesets; //Multidimensional vector to hold map
	vector<vector<string>> maptxt; //Real 2d representation of map
	std::map<int, std::map<int, vector<string>>> worldmap; //2d map to identify chunks of map
	sf::Sprite tile; //Sprite for single tile
	TILE selectTile(int no); //Selects the texture rect corresponding an specific tile
	vector<TILE> sprites; //Vector of sprites for tile drawing
	void createSprite(int no); //Pushes new sprites to back of lists
private:
	const static int chunksize = 16; //Chunk size ALWAYS 16
	void mapFitter(); //(chunkLoader) Transforms tilesets vector into full 2d map: maptxt
	unsigned int it; //Number of chunks, registered to make corresponding vectors
	bool firstrun; //(drawMap) 
	vector<int>xattr; //List of all x attributes in map
	vector<int>yattr; //List of all y attributes in map
	pugi::xml_attribute x, y; //x and y attributes in chunk nodes in xml
	sf::Texture tileset; //Tileset texture in game class
	sf::Vector2i tiles; //Number of tiles in tileset
	sf::Vector2i tsize; //Tile size (width and height)
	sf::Vector2i upleft; //Leftdown vertex of mp
	sf::Vector2i downright; //Upright vertex of map 
	sf::Vector2i tilecount; //No of tiles in tileset image


};



#endif

