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
  void setup(Megaman& player); //Setup runned only once
  void handleInput(sf::Event event); //Gives a response depending on input
  void update(Megaman& player, sf::Time deltatime); //Updates game logic
  void render(sf::RenderWindow& window); //Renders on screen
  void cancelInput(); //Cancels input after releasing mouse
  setMegaReference(Megaman& ref) //Sets intern pointer to megaman object
  float speed;
private:
  void handleKey(sf::Keyboard::Key key); //(handleInput) Returns which arrow has been pressed
  void movePlayer(Megaman& target, sf::Time deltatime); //(Update) Updates player movement
  void setBG(); //(Setup) Sets background
  Megaman& mega;
  bool up, down, left, right, jump; //Represent pressed key
};

#endif
