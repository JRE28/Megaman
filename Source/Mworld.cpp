#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Mworld.h"
#include "Megaman.h"
using namespace std;

Mworld::Mworld(float chrspeed)
{
  speed = chrspeed; //Player speed
}

void Mworld::setup(Megaman& player)
{
  player.setTexture("../Resources/megaman.png");
}

void Mworld::handleInput(sf::Event event)
{
  switch(event.type)
  {
    case sf::Event::KeyPressed:
      handleKey(event.key.code);
      break;
  }
}

void setMegaReference

void Mworld::handleKey(sf::Keyboard::Key key)
{
  switch(key)
  {
    case sf::Keyboard::Up:
      up = true;
    case sf::Keyboard::Down:
      down = true;
      break;
    case sf::Keyboard::Left:
      left = true;
      break;
    case sf::Keyboard::Right:
     right = true;
     break;
    case sf::Keyboard::Space:
      jump = true;
      break;
  }
}

void Mworld::update(Megaman& player, sf::Time deltatime)
{
  movePlayer(player, deltatime);
}

void Mworld::movePlayer(Megaman& target, sf::Time deltatime)
	{
		sf::Vector2f movement(0,0);
		if(up)	//Gets which key is pressed and moves referenced sprite in consequence
		{
			movement.y -= speed;
		}if(down)
		{
			movement.y += speed;
		}if(left)
		{
			movement.x -= speed;
		}if(right)
		{
			movement.x += speed;
		}
		target.sprite.move(movement * deltatime.asSeconds()); //Distance = speed * time elapsed
	}

void Mworld::render(sf::RenderWindow& window)
{
  window.draw()
}
