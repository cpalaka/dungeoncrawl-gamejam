#ifndef ENEMY_H
#define ENEMY_H

#define BLACK 0
#define WHITE 1

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "AnimationObject.h"
enum enemytype { Bat = 6, 
				 Skeleton,
				 TrollArcher };

class Enemy {
public:
	Enemy(enemytype, int, int);
	void update(double, int ,int, int**, int& playerHP);
	void draw(sf::RenderWindow&);
	void attack();
	bool active;
	int x, y;
	enemytype type;
private:
	//sf::Texture enemytexture;
	sf::Texture bat, skeleton, trollarcher;
	sf::Sprite bats, skeletons, trollarchers;
	//AnimationObject anim;
	double deltasum;
	int range;
	
	int HP;
	int damage;
	int speed;
};
#endif ENEMY_H