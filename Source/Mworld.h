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
  float speed; //Player speed
  Megaman* mega; //Pointer to megaman object
private:
  void handleKey(sf::Keyboard::Key key); //(handleInput) Returns which arrow has been pressed
  void movePlayer(sf::Time deltatime); //(Update) Updates player movement
  void setBG(); //(Setup) Sets background
  bool up, down, left, right, jump; //Represent pressed key
};

#endif
