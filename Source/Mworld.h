#ifndef MWORLD_H
#define MWORLD_H
#include <iostream>
#include <SFML/Graphics.hpp>
 #include "Megaman.h"
using namespace std;

class Mworld
{
public:
  Mworld(float chrspeed);
  void setup(); //Setup runned only once
  void handleInput(sf::Event event); //Gives a response depending on input
  void update(sf::Time deltatime); //Updates game logic
  void render(sf::RenderWindow& window); //Renders on screen
  void cancelInput(); //Cancels input after releasing mouse
  void timeLimit(int movtype); //Determines time for specific animations
  void idle(); //Manages idle position
  void gravity(float accel); //Creates a gravity field on player
  void airtime(); //Calculates time on air
  float speed; //Player speed
  int movement; //Moving direction depending on input
  Megaman* mega; //Pointer to megaman object
private:
  void handleKey(sf::Keyboard::Key key); //(handleInput) Returns which arrow has been pressed
  void movePlayer(sf::Time deltatime); //(Update) Updates player movement
  void setBG(); //(Setup) Sets background
  bool up, down, left, right, jump; //Represent pressed key
  float tlimit; //Animation limit time
  float timeonair; //(gravity)Time mega is on air after jumping or falling
  float jumpforce;
  sf::RectangleShape floor;
  sf::Clock airclock; //Clock for air time
  sf::Time zero;
  bool floating;


};

#endif
