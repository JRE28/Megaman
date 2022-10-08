#include <iostream>
#include "pugixml.hpp"
#include "Map.h"
#include <SFML/Graphics.hpp>
using namespace std;

sf::RenderWindow window(sf::VideoMode(1600, 900), "kalboooooooo");
int x = 0;
int icount = 0;

int main()
{
	sf::Event event;
		Map map("bombman.tmx", 10, 6);
		map.setTexture("../../Resources/bombman.png");
		map.chunkParent = map.doc.child("map").child("layer").child("data");
		map.chunkLoader();
	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{

			if(event.type == sf::Event::Closed)
			{
					window.close();
			}
		}
		window.clear(sf::Color::White);
		/*icount = 0;	
		for(auto u : map.worldmap[16][0])
		{
			map.createSprite(stoi(u));
			map.sprites[icount].sprite.setPosition(16*icount, 100);
			window.draw(map.sprites[icount].sprite);
			cout << icount << " ";
			icount++;
		}*/

		map.drawMap(window,0);
		map.sprites[268].sprite.setPosition(600,600);
		window.display();
	}
}