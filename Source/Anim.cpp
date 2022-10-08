#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Anim.h"
using namespace std;


Anim::Anim(int x, int y) //Number of frames in picture, for animation
{
	imageCount.x = x;
	imageCount.y = y;
	currentimage.x = 0;
	currentimage.y = 0;
	BGset = false; //Remains false until setBG is runned
}

bool Anim::setTexture(string dir)
{
	if(!texture.loadFromFile(dir))
	{
		cout << "Not loaded!" << endl;
		return false;
	}
	this->sprite.setTexture(texture);
	size = texture.getSize();
	return true;
}


void Anim::setBG(int scrX, int scrY)
{
	this->width = size.x / imageCount.x; //Width of single frame (considering they're equal)
	this->height = size.y / imageCount.y; //Height of single frame
	this->scale.x = (float) scrX / width; //Ratio needed to fit image to width
	this->scale.y = (float) scrY / height; //Ratio to fit image to height
	this->sprite.setTextureRect(sf::IntRect(width*currentimage.x, height*currentimage.y, width*(currentimage.x+1), height*(currentimage.y+1)));
	//Reduces rectangle to selected frame using currentimage vector
	this->sprite.setScale(scale.x, scale.y); //Fits to background
	this->sprite.setPosition(0,0); //Sets the position in 0
}	

void Anim::transition()
{
	if(this->currentimage.x+1 == this->imageCount.x) //Cheks if Currentimage last in row
	{
		if(this->currentimage.y+1 < this->imageCount.y) //Checks if currentimage is not last in column
		{
			this->currentimage.y++; //If so, passes to the next one
		}
		else
		{
			this->currentimage.y = 0;
		}
		this->currentimage.x = 0; //Row is 0
	}
	else
	{
		this->currentimage.x++; //Adds one to x if it's not last in row
	}
}

void Anim::update(sf::Time dt, float limit)
{
	if(timer >= sf::seconds(limit))
	{
		this->transition();
		this->sprite.setTextureRect(sf::IntRect(width*currentimage.x, height*currentimage.y, width*(currentimage.x+1), height*(currentimage.y+1)));
		timer = sf::seconds(0);
	}
	else
	{
		timer += dt;
	}
}