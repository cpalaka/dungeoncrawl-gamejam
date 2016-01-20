#include "Enemy.h"

Enemy::Enemy(enemytype _type, int _x, int _y) :
	active(false),
	deltasum(0)
{
	x = _x;
	y = _y;
	type = _type;

	
	if(type == Bat)
	{
		HP = 30;
		damage = 5;
		speed = 5;
		range = 1;
		bat.loadFromFile("resources/graphics2/bat.png");
		bats.setTexture(bat);
		bats.setPosition(x*20, y*20);
	}
	if(type == Skeleton)
	{
		HP = 50;
		damage = 9;
		speed = 4;
		range = 1;
		skeleton.loadFromFile("resources/graphics2/skeleton.png");
		skeletons.setTexture(skeleton);
		bats.setPosition(x*20, y*20);
	}
	if(type == TrollArcher)
	{
		HP = 50;
		damage = 13;
		speed = 4;
		range = 4;
		trollarcher.loadFromFile("resources/graphics2/goblinarcher.png");
		trollarchers.setTexture(trollarcher);
		bats.setPosition(x*20, y*20);
	}

	/*
	bat.loadFromFile("resources/graphics/bat.png");
	skeleton.loadFromFile("resources/graphics/skeleton.png");
	trollarcher.loadFromFile("resources/graphics/goblinarcher.png");
	anim.addAnimation(bat, "bat", 6, 0);
	anim.addAnimation(skeleton, "skeleton", 8, 0);
	anim.addAnimation(trollarcher, "trollarcher", 8, 0);
	*/
}


void Enemy::update(double deltatime, int x, int y, int** grid, int& playerHP)
{
	deltasum += deltatime;

	

	if(deltasum > 2000 - speed*100 && active)
	{

		 if(abs(this->x-x)+abs(this->y-y)<=range)
		{
			 playerHP-=damage;
			//std::cout<<playerHP<<std::endl;
		}
		else
		{
		if(this->x>x&&grid[this->x-1][this->y]==WHITE&&rand()%2==0)
		    this->x--;
		else if(this->x<x&&grid[this->x+1][this->y]==WHITE&&rand()%2==0)
		    this->x++;
		if(this->y>y&&grid[this->x][this->y-1]==WHITE&&rand()%2==0)
			 this->y--;
		 else if(this->y<y&&grid[this->x][this->y+1]==WHITE&&rand()%2==0)
			this->y++;
		 }
		deltasum = 0;
	}

	if(type == Bat)
	{
		bats.setPosition(x*20, y*20);
	} else if(type == Skeleton)
	{
		skeletons.setPosition(x*20, y*20);
	}
	else if(type == TrollArcher)
	{
		trollarchers.setPosition(x*20, y*20);
	}
	//anim.xpos = x*20;
	//anim.ypos = y*20;
}

void Enemy::draw(sf::RenderWindow& window)
{
	
	/*
	else if(type == Skeleton)
		anim.setCurrentAnim("skeleton");
	else if(type == TrollArcher)
		anim.setCurrentAnim("trollarcher");
		*/
	if(type == Bat)
		window.draw(bats);
	if(type == Skeleton)
		window.draw(skeletons);
	if(type == TrollArcher)
		window.draw(trollarchers);
}