#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Mworld.h"
#include "Megaman.h"
#include "Map/Map.h"
using namespace std;

Mworld::Mworld(float chrspeed)
{
  speed = chrspeed; //Player speed
  zero = sf::seconds(0);
  floating = false;
  timeonair = 0;
  jumpforce = 400;
  jumping = false;
  gravityforce = 2;
}




void Mworld::handleInput(sf::Event event)
{

  if(event.type == sf::Event::KeyPressed)
  {
    handleKey(event.key.code);
  }
  if(jumping && left)
  {
    movement = mega -> jmpl;
  }
  if(jumping && right)
  {
    movement = mega->jmpr;
  }
  if(jumping && (movement == mega->idlelft))
  {
    movement = mega->jmpl;
  }
  if(jumping && (movement == mega->idlerght))
  {
    movement = mega->jmpr;
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
  if(movement == mega->rght || (movement == mega->jmpr && mega->onfloor))
  {
    movement = mega->idlerght;
    right = false;
    mega->update(movement, zero, 0);
  }
  if(movement == mega->lft || (movement == mega->jmpl && mega->onfloor))
  {
    movement = mega->idlelft;
    left = false;
    mega->update(movement, zero, 0);
  }

}

void Mworld::cancelJump() {jump = false;}

void Mworld::jmp(sf::Time dtime, float limit)
{
  if(mega->onfloor)
  {
    jumping = false;
    if(jumpidle)
    {
      idle();
      jumpidle = false;
    }
  }
  if(mega->onfloor && jump)
  {
    jumping = true;
    jumpidle = true;
  }
  if(jumping)
  {
    mega->update(movement, zero, 0);
    gravityforce = 2;
    mega->sprite.move(sf::Vector2f(0, -jumpforce) * dtime.asSeconds()); //Distance = speed * time elapsed
    if(timeonair >= limit) //When time finishes, gravity comes back
    {
      jump = false;
      gravityforce = 2;
    }
  }
}

void Mworld::cancelInput(sf::Keyboard::Key key)
{
    switch(key)
    {
      case sf::Keyboard::Left:
        left = false;
        break;
      case sf::Keyboard::Right:
        right = false;
        break;
    }
}

void Mworld::timeLimit(int movtype)
{
  if(movtype == mega->idlelft || movtype == mega->idlerght)
  {tlimit = 1;}
  else{tlimit = 0.2;}
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

  void Mworld::setup()
  {
    mega->setTexture("../Resources/megaman.png");
    floor.setSize(sf::Vector2f(1000,100));
    floor.setFillColor(sf::Color::Black);
    floor.setPosition(0, 1000);
    floor.setOutlineColor(sf::Color::Red);
    floor.setOutlineThickness(5);
  }

  void Mworld::update(sf::Time deltatime)
  {
    mega->collisioncheck(floor);
    gravity(gravityforce);
    jmp(deltatime, 0.5);
    movePlayer(deltatime);
    mega->update(movement, deltatime, tlimit);
    timeLimit(movement);

  }
void Mworld::render(sf::RenderWindow& window)
{
  window.draw(mega->sprite);
  window.draw(floor);
  window.display();
}
