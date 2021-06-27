#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Mworld.h"
#include "Megaman.h"
using namespace std;

Mworld::Mworld(float chrspeed)
{
  speed = chrspeed; //Player speed
  zero = sf::seconds(0);
  timeonair = 0;
  jumpforce = 30;
}

void Mworld::setup()
{
  mega->setTexture("../Resources/megaman.png");
  mega->onfloor = false;
  floor.setSize(sf::Vector2f(1000,100));
  floor.setFillColor(sf::Color::Black);
  floor.setPosition(0, 700);
  floor.setOutlineColor(sf::Color::Red);
  floor.setOutlineThickness(5);
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
      movement = mega->lft;
      break;
    case sf::Keyboard::Right:
     right = true;
     movement = mega->rght;
     break;
    case sf::Keyboard::Space:
      jump = true;
      cout << "A";
      break;
  }
}

void Mworld::idle()
{
  if(movement == mega->rght)
  {
    movement = mega->idlerght;
    mega->update(movement, zero, 0);
  }
  else if(movement == mega->lft)
  {
    movement = mega->idlelft;
    mega->update(movement, zero, 0);
  }

}
void Mworld::cancelInput()
{
  up = false;
  down = false;
  left = false;
  right = false;
  jump = false;
}

void Mworld::timeLimit(int movtype)
{
  if(movtype == mega->idlelft || movtype == mega->idlerght)
  {tlimit = 1;}
  else{tlimit = 0.2;}
}

void Mworld::update(sf::Time deltatime)
{
  mega->collisioncheck(floor);
  gravity(2);
  movePlayer(deltatime);
  timeLimit(movement);
  mega->update(movement, deltatime, tlimit);
  cancelInput();
}

void Mworld::airtime()
{
  if(!mega->onfloor)
  {
    if(!floating)
    {
      airclock.restart();
    }
    floating = true;
    timeonair = airclock.getElapsedTime().asSeconds();
  }
  if(mega->onfloor)
  {
    floating = false;
    timeonair = 0;
  }
}

void Mworld::gravity(float accel)
{
  airtime();
  mega->sprite.move(sf::Vector2f(0, accel*timeonair));
}

void Mworld::movePlayer(sf::Time deltatime)
	{
		sf::Vector2f movement(0,0);
		if(jump)	//Gets which key is pressed and moves referenced sprite in consequence
		{
			movement.y -= jumpforce;
		}if(left)
		{
			movement.x -= speed;
		}if(right)
		{
			movement.x += speed;
		}
		mega->sprite.move(movement * deltatime.asSeconds()); //Distance = speed * time elapsed
	}

void Mworld::render(sf::RenderWindow& window)
{
  window.draw(mega->sprite);
  window.draw(floor);
  window.display();
}
