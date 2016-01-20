#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Window.hpp>
#include "AnimationObject.h"
#include "InitalMenu.h"

#define BLACK 0
#define WHITE 1

const unsigned int scale = 20;

class Player {
public:
	Player(int, int);
	int x, y; //grid locations (not pixels)
	void update(double, sf::Event, int**);
	void draw(sf::RenderWindow&);
	void setValues(HeroValues);
	int HP;
	AnimationObject anim;
private:
	 //this holds the pixel position of the drawn sprite/anim
	sf::Texture idle, walkleft, walkright, walkup, walkdown, attackleft, attackright, attackup, attackdown;
	bool move[4];//up left down right (handles which key is pressed)
	bool dir[4];//up left down right (handles the direction the player is moving in/facing)
	int damage;
	int speed;
	double deltasum;
};

#endif PLAYER_H