#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Megaman.h"
using namespace std;


Megaman::Megaman(int xcount, int ycount)
{
	imageCount.x = xcount;
	imageCount.y = ycount;
	currentimage.x = 0;
	currentimage.y = 0;
}


bool Megaman::setTexture(string directory)
{
	if(texture.loadFromFile(directory))
	{
		sprite.setTexture(texture);
		size = texture.getSize();
		this->fwidth = size.x / imageCount.x; //Width of single frame (considering they're equal)
		this->fheight = size.y / imageCount.y; //Height of single frame
		return true; //If everything went well, returns true
	}
	else
	{

		return false;
	}
}

void Megaman::setSize(int width, int height)
{
	this->sprite.setScale(width/this->texture.getSize().x, height/this->texture.getSize().y);
}


void Megaman::transition(int movtype)
{
	switch(movtype)
	{
		case this->idlelft:
			xframes = 3;
			break;
		case this->idlerght:
			xframes = 3;
			break;
		case this->rght:
			xframes = 4;
			break;
		case this->lft:
			xframes = 4;
			break;
	}
	if(this->currentimage.x+1 >= xframes) //Checks if Currentimage last in row
	{
		this->currentimage.x = 0;
	}
	else
	{
		this->currentimage.x++; //Adds one to x if it's not last in row
	}
}

void Megaman::update(int movtype, sf::Time dt, float limit)
{
	currentrow = 0;
	if(timer >= sf::seconds(limit))
	{
		this->transition(movtype);
		this->sprite.setTextureRect(sf::IntRect(fwidth*currentimage.x, fheight*currentrow, fwidth*(currentimage.x+1), fheight*(currentrow+1)));
		timer = sf::seconds(0);
	}
	else
	{
		timer += dt;
	}
}

void Megaman::selectRow(int row)
{
  currentimage.y = row-1;
}
