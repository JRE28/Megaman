#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Mworld.h"
#include "Megaman.h"
#include "ResourceHandler.h"
using namespace std;

Mworld::Mworld(float chrspeed)
{
  speed = chrspeed; //Player speed
  zero = sf::seconds(0);
  floating = false;
  timeonair = 0;
  jumpforce = 900;
  jumping = false;
  gravityforce = 2;
}

void Mworld::setup()
{
  mega->setTexture("../Resources/megaman.png");
  floor.setSize(sf::Vector2f(1000,100));
  floor.setFillColor(sf::Color::Black);
  floor.setPosition(0, 700);
  floor.setOutlineColor(sf::Color::Red);
  floor.setOutlineThickness(5);
}



void Mworld::handleInput(sf::Event event)
{

  if(event.type == sf::Event::KeyPressed)
  {
    handleKey(event.key.code);
  }
}


void Mworld::handleKey(sf::Keyboard::Key key)
{
  if(key == sf::Keyboard::Left)
  {
    left = true;
    movement = mega->lft;
  }
  if(key == sf::Keyboard::LAlt)
  {
    jump = true;
  }
  if(key == sf::Keyboard::Right)
  {
    right = true;
    movement = mega ->rght;
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

void Mworld::cancelJump() {jump = false;}

void Mworld::jmp(sf::Time dtime, float limit)
{
  if(mega->onfloor && jump)
  {
    jumping = true;
  }
  if(jumping)
  {
    gravityforce = 2;
    mega->sprite.move(sf::Vector2f(0, -jumpforce) * dtime.asSeconds()); //Distance = speed * time elapsed
    if(timeonair >= limit) //When time finishes, gravity comes back
    {
      jump = false;
      gravityforce = 2;
      jumping = false;
    }
  }
}

void Mworld::cancelInput()
{
  down = false;
  left = false;
  right = false;
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
  gravity(gravityforce);
  jmp(deltatime, 0.1);
  movePlayer(deltatime);
  timeLimit(movement);
  mega->update(movement, deltatime, tlimit);
  cancelJump();
}

float Mworld::airtime()
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
  return timeonair;
}

void Mworld::gravity(float accel)
{
  airtime();
  mega->sprite.move(sf::Vector2f(0, accel*timeonair));
}

void Mworld::movePlayer(sf::Time deltatime)
	{
		sf::Vector2f movement(0,0);
    if(jumping)
    {
      movement.y -= jumpforce;
    }
		if(left)
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
