#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Megaman.h"
#include "Mworld.h"
using namespace std;

int scrX = 1200;
int scrY = 800;
Mworld game(50);
Megaman mega(4,4);
sf::RenderWindow window(sf::VideoMode(scrX, scrY), "Megaman");
sf::Event event;


int main()
{
  game.mega = &mega;
  sf::Clock clock;
  sf::Time dtime;
  game.setup();
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
    dtime = clock.restart();
    game.handleInput(event);
    game.update(dtime);
    game.render(window);
  }
}
