#ifndef RESOURCEHANDLER_H
#define RESOURCEHANDLER_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;

class ResourceHandler
{
public:
	bool loadSound(string filename); //Loads sound
	void play(sf::SoundBuffer buff);

private:
	sf::SoundBuffer buffer;
	sf::Sound temp;
	sf::Sound GRuiz;
};

#endif