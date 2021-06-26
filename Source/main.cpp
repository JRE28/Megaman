#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Megaman.h"
#include "Mworld.h"
using namespace std;

int scrX = 1200;
int scrY = 800;
Mworld game(5);
Megaman mega(4,4);e
sf::RenderWindow window(sf::VideoMode(scrX, scrY), "Megaman");
sf::Event event;


int main()
{
  sf::Clock clock;
  sf::Time dtime;
  while(window.isOpen())
  {
    while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
					window.close();
			}
		}
    window.display(0);
    dtime = clock.restart();
    game.handleInput(event);
    game.update(mega, dtime);
    game.render(window);
  }
}
