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


void Megaman::transition()
{
	if(this->currentimage.x+1 == this->imageCount.x) //Checks if Currentimage last in row
	{
		this->currentimage.x = 0;
	}
	else
	{
		this->currentimage.x++; //Adds one to x if it's not last in row
	}
}

void Megaman::update(sf::Time dt, float limit)
{
	if(timer >= sf::seconds(limit))
	{
		this->transition();
		this->sprite.setTextureRect(sf::IntRect(fwidth*currentimage.x, fheight*currentimage.y, fwidth*(currentimage.x+1), fheight*(currentimage.y+1)));
		timer = sf::seconds(0);
	}
	else
	{
		timer += dt;
	}
}
