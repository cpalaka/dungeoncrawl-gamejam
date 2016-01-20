#ifndef LEVEL_H
#define LEVEL_H

#include <SFML\Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "InitalMenu.h"

enum leveltype {Begin, Dungeon, GameOver};

class Level {
public:
	Level(int depth);
	~Level();
	void update(double deltatime, sf::Event evt, sf::View&);
	void draw(sf::RenderWindow&);
	void setLevel(leveltype);
	void getentityPos();
	leveltype currentleveltype;
	void recalculate(int);
private:
	Map* map;
	//int mapheight, mapwidth;
	Player* player;
	sf::Vector2i playerpos;
	std::vector<entity> elist;
	std::vector<Enemy> enemylist;
	HeroValues values;
	sf::Texture wall, ground1, ground2, chest, ground1fade, ground2fade, wallfade, stair;
	sf::Sprite walls, ground1s, ground2s, chests, ground1fades, ground2fades, wallfades, stairs;
	InitialMenu* imenu;
	unsigned int depthcount;
	int dist(int,int,int,int);
	int **seen; // 0 - not seen, 1 - seen, 2 - currently seen
};

#endif LEVEL_H