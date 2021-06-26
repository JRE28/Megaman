#ifndef MEGAMAN_H
#define MEGAMAN_H
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Megaman
{
public:
	Megaman(int xcount, int ycount); //xcount & ycount represent frames in texture
	bool setTexture(string directory); //Sets texture to sprite
	void setSize(int swidth, int sheight); //Scales sprite to fit designed size
	void nextFrame();
	void update(sf::Time dt, float limit); //Changes to new frames, animating it
	sf::Sprite sprite; //Player sprite
	sf::Vector2f pos; //Player's position
	sf::Vector2u imageCount; //Number and location of total images in texture
	sf::Vector2u currentimage; //Image selected
	sf::Vector2u size; //Size of complete texture
private:
	sf::Texture texture; //Player texture
	void transition(); //Changes showed frame
	sf::Time timer; //Internal timer for update functions
	float fwidth, fheight; //Texture frame width and
};


#endif
