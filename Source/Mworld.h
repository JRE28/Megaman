#ifndef MWORLD_H
#define MWORLD_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Megaman.h"
#include "Map/Map.h"
using namespace std;

class Mworld
{
public:
  Mworld(float chrspeed);
  void setup(); //Setup runned only once
  void handleInput(sf::Event event); //Gives a response depending on input
  void update(sf::Time deltatime); //Updates game logic
  void render(sf::RenderWindow& window); //Renders on screen
  void cancelInput(sf::Keyboard::Key key); //Cancels input after releasing mouse
  void cancelJump(); //Jump = false
  void timeLimit(int movtype); //Determines time for specific animations
  void idle(); //Manages idle position
  void jmp(sf::Time dtime, float limit); //Makes mega jump
  void gravity(float accel); //Creates a gravity field on player
  float airtime(); //Calculates time on air
  float speed; //Player speed
  int movement; //Moving direction depending on input
  bool jump, right;
  Megaman* mega; //Pointer to megaman object
  float timeonair; //(gravity)Time mega is on air after jumping or falling
  int gravityforce; //gravity force
  sf::Sprite BG; //Background sprite
  sf::Texture BGtexture; //Background texture
private:
  void handleKey(sf::Keyboard::Key key); //(handleInput) Returns which arrow has been pressed
  void movePlayer(sf::Time deltatime); //(Update) Updates player movement
  bool down, left; //Represent pressed key
  float tlimit; //Animation limit time
  float jumpforce; //Jump strength
  sf::RectangleShape floor; //Floor shape
  sf::Clock airclock; //Clock for air time
  sf::Clock jmpclock; //Clock for jumping
  sf::Time jmptimer; //Timer for jumping
  sf::Time zero; //Represents zero time
  float jmptime;
  bool floating; //Logical boolean for air time and gravity
  bool jumping;
  bool jumpidle; //Used to change frames after jumping


};

#endif
