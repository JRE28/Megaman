#ifndef ANIM_H
#define ANIM_H
using namespace std;

class Anim
{
public:
	Anim(int x, int y); //Sets the number of frames in image
	sf::Sprite sprite; //Animation sprite
	sf::Texture texture; //Animation texture
	sf::Vector2u imageCount; //Number and location of total images in a background
	sf::Vector2u currentimage; //Image selected
	sf::Vector2u size; //Size of complete texture
	bool setTexture(string dir); //if texture doesn't load, returns false; else, true
	void setBG(int scrX, int scrY); //Run once, sets up the background, ready to be animated
	void update(sf::Time dt, float limit); //Changes background to new frames, animating it
	void transition();
protected:
	int height;
	int width; //Texture width
	bool BGset; //Once BG is set, becomes true
	sf::Vector2f scale; //Scale to fit background image
	sf::Time timer; //Internal timer for update functions

};

#endif