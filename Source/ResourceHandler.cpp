#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourceHandler.h"
using namespace std;

bool ResourceHandler::loadSound(string filename)
{
    if(this->buffer.loadFromFile(filename))
    {
    	return true;
    }
    else {return false;}
}

void ResourceHandler::play(sf::SoundBuffer buff)
{
	temp.setBuffer(buff);
	temp.play();
}