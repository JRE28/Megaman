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
	void collisioncheck(sf::RectangleShape rect);
	void update(int movtype, sf::Time dt, float limit); //Changes to new frames, animating it
	void selectRow(int row); //Changes texture row for different movements
	sf::Sprite sprite; //Player sprite
	sf::Vector2f pos; //Player's position
	sf::Vector2u imageCount; //Number and location of total images in texture
	sf::Vector2u currentimage; //Image selected
	sf::Vector2u size; //Size of complete texture
	static const unsigned int idlelft = 0, idlerght = 1, rght = 2, lft = 3, jmpl = 4, jmpr = 5;
	bool onfloor; //States if mega is on air or on the floor
	//Movement types for transition()
private:
	sf::Texture texture; //Player texture
	void transition(int movtype); //Changes showed frame
	sf::Time timer; //Internal timer for update functions
	sf::IntRect HitBox;
	int fwidth, fheight; //Texture frame width and Height
	unsigned int xframes; //Number of frames in x a row
};


#endif
