#include "Player.h"

Player::Player(int _x, int _y) :
	deltasum(0)
{
	x = _x;
	y = _y;

	//set all player movement to false
	for(int i = 0; i < 4; ++i) move[i] = 0;
	for(int i = 0; i < 4; ++i) dir[i] = 0;

	idle.loadFromFile("resources/graphics/swordmanidle.png");
	anim.addAnimation(idle, "idle", 1, 1);
	anim.setCurrentAnim("idle");
}

void Player::update(double deltatime, sf::Event evt, int** grid)
{
	deltasum += deltatime;

	
	if(evt.type == sf::Event::KeyPressed)
	{
			switch(evt.key.code)
			{
			case sf::Keyboard::W:
				move[0] = true;
				break;
			case sf::Keyboard::A:
				move[1] = true;
				break;
			case sf::Keyboard::S:
				move[2] = true;
				break;
			case sf::Keyboard::D:
				move[3] = true;
				break;
			}
	}

	if(evt.type == sf::Event::KeyReleased)
	{
		switch(evt.key.code)
		{
			case sf::Keyboard::W:
				move[0] = false;
				break;
			case sf::Keyboard::A:
				move[1] = false;
				break;
			case sf::Keyboard::S:
				move[2] = false;
				break;
			case sf::Keyboard::D:
				move[3] = false;
				break;
		}
	}

	if(deltasum > 1500 - speed*100)
	{
		if(move[0] && grid[x][y-1] == WHITE)
		{
			--y;
			dir[0] = 1;
			dir[1] = 0;
			dir[2] = 0;
			dir[3] = 0;
		}
		if(move[1] && grid[x-1][y]== WHITE)
		{
			--x;
			dir[1] = 1;
			dir[0] = 0;
			dir[2] = 0;
			dir[3] = 0;
		}
		if(move[2] && grid[x][y+1]== WHITE)
		{
			++y;
			dir[2] = 1;
			dir[1] = 0;
			dir[0] = 0;
			dir[3] = 0;
		}
		if(move[3] && grid[x+1][y] == WHITE)
		{	
			++x;
			dir[3] = 1;
			dir[0] = 0;
			dir[1] = 0;
			dir[2] = 0;
		}

		deltasum = 0;
		anim.xpos = x*scale;
		anim.ypos = y*scale;
	} else {
		if(deltasum > (1500 - speed*100)/2)
		{
		
		}

		//experimental smoothing of player movement
		if(move[0])// && dir[0])
		{
			anim.ypos = anim.ypos - deltatime/(1500 - speed*100)*scale;
		} 
		if(move[1])// && dir[1])
		{
			anim.xpos = anim.xpos - deltatime/(1500 - speed*100)*scale;
		}
		if(move[2])// && dir[2])
		{
			anim.ypos = anim.ypos + deltatime/(1500 - speed*100)*scale;
		}
		if(move[3])// && dir[3])
		{
			anim.xpos =anim.xpos + deltatime/(1500 - speed*100)*scale;
		}
	}
	/*
	for(int i = 0; i<4; i++)
	{
		if(dir[0]) std::cout<<"1 ";
		else std::cout<<"0 ";
		if(dir[1]) std::cout<<"1 ";
		else std::cout<<"0 ";
		if(dir[2]) std::cout<<"1 ";
		else std::cout<<"0 ";
		if(dir[3]) std::cout<<"1 ";
		else std::cout<<"0 ";
		std::cout<<std::;
	}
	*/
}

void Player::draw(sf::RenderWindow& window)
{
	anim.draw(window);
}

void Player::setValues(HeroValues v)
{
	HP = v.HP;
	damage = v.damage;
	speed= v.speed;
	//speed = 20;
}

