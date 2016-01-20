#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "Level.h"
#include <chrono>

class Game {
public:
	Game();
	void start();
	void gameloop();
private:
	sf::RenderWindow window;
	sf::View view;
	Level* currentlevel;
	double deltatime;
};

#endif GAME_H