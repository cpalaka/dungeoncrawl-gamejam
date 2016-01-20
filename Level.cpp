#include "Level.h"

Level::Level(int depth) 
{
	depthcount = depth;
	player = NULL;
	imenu = NULL;
	map = NULL;
	
	wall.loadFromFile("resources/graphics/wall.png");
	walls.setTexture(wall);

	ground1.loadFromFile("resources/graphics/ground2.png");
	ground1s.setTexture(ground1);

	ground2.loadFromFile("resources/graphics/ground3.png");
	ground2s.setTexture(ground2);

	chest.loadFromFile("resources/graphics/chest.png");
	chests.setTexture(chest);

	ground1fade.loadFromFile("resources/graphics/ground2fade.png");
	ground1fades.setTexture(ground1fade);

	ground2fade.loadFromFile("resources/graphics/ground3fade.png");
	ground2fades.setTexture(ground2fade);

	wallfade.loadFromFile("resources/graphics/wallfade.png");
	wallfades.setTexture(wallfade);

	stair.loadFromFile("resources/graphics/stairs.png");
	stairs.setTexture(stair);

}

Level::~Level()
{
	delete map;
	delete player;
	delete imenu;
}

void Level::update(double deltatime, sf::Event evt, sf::View& view)
{
	switch(currentleveltype)
	{
	case Begin:
		if(!imenu->done)
		{
			imenu->update(deltatime, evt);
			break;
		} else {
			values = imenu->getValues();
			currentleveltype = Dungeon;
		}
		break;
	case Dungeon:
	
		srand(time(0));
		
		//generate a map based on current depth
		if(depthcount<5 && map == NULL) 
		{
			map = new Map(40, 40);
			map->createMap(30 + rand()%10, 2+rand()%2, 3 + rand()%4, 3);
			map->addMonsters(5 + rand()%6, 8, 10, 100);
			map->drawMap();
			seen = new int*[map->height];
	
			for(int i = 0; i < map->height; ++i)
			{
			seen[i] = new int[map->width]();
			}
			//debug only
			/*
			for(int x = 0; x < map->height; ++x)
			{
				for(int y = 0; y< map->width; ++y)
				{
					seen[x][y] = 1;
				}
			}
				*/	
			elist = map->retrieveEntityList();
			getentityPos();
			player = new Player(playerpos.x, playerpos.y); player->setValues(values);
			
		}

		
		//initialize seen array

		recalculate(8);
		auto itr = enemylist.begin();
		for(itr; itr != enemylist.end(); ++itr)
		{
			itr->update(deltatime, player->x, player->y, map->grid, player->HP);
		}
		player->update(deltatime, evt, map->grid);

		view.setCenter(player->anim.xpos, player->anim.ypos);
		//recalculate seen array

		break;
	}
	
}

void Level::draw(sf::RenderWindow& window)
{
	//std::cout<<"DRAW\n";
	if(currentleveltype == Begin)
	{
		if(!imenu->done)
		{
			imenu->draw(window);
		}
	}
	else if(currentleveltype == Dungeon)
	{
		if(map != NULL)
		{
		
		for(int i = 0; i<map->height; ++i)
		{
			for(int j = 0; j<map->width; ++j)
			{
				if(seen[i][j] == 1) // seen (but not currently)
				{
					//if ground
					if(map->grid[i][j] == WHITE)
					{
						ground1fades.setPosition(i*20, j*20);
						window.draw(ground1fades);
					}
					//if wall
					if(map->grid[i][j] == WALL)
					{
						wallfades.setPosition(i*20, j*20);
						window.draw(wallfades);
					}
				}
				if(seen[i][j] == 2) // currently seen
				{
					//if ground
					if(map->grid[i][j] == WHITE)
					{
						ground1s.setPosition(i*20, j*20);
						window.draw(ground1s);
					}
					//if wall
					if(map->grid[i][j] == WALL)
					{
						walls.setPosition(i*20, j*20);
						window.draw(walls);
					}
					
					if(map->grid[i][j] == TREASURE)
					{
						chests.setPosition(i*20, j*20);
						window.draw(chests);
					}
					if(map->grid[i][j] == LADDER || map->grid[i][j] == START)
					{
						stairs.setPosition(i*20, j*20);
						window.draw(stairs);
					}
					auto itr = enemylist.begin();
					for(; itr != enemylist.end(); ++itr)
					{
						//ground1s.setPosition(itr->x*20, itr->y*20);
						
						//window.draw(ground1s);

						itr->draw(window);
						//std::cout<<"drawn enemy"<<std::endl;
					}
				}
			}
		}
		
		player->draw(window);
		}
	}
}

void Level::setLevel(leveltype leveltype)
{
	currentleveltype = leveltype;
	switch(leveltype)
	{
	case Begin:
		imenu = new InitialMenu();
		break;
	case Dungeon:

		break;
	}
}

void Level::getentityPos()
{
	//map->drawMap();
	//std::sort(elist.begin(), elist.end());
	auto itr = elist.begin();
	for(itr; itr != elist.end(); ++itr)
	{
		if(itr->entityNo == START) 
		{
			playerpos.x = itr->x; 
			playerpos.y = itr->y;
		}
		if(itr->entityNo == BAT) 
		{
			Enemy e(Bat, itr->x, itr->y);
			enemylist.push_back(e);
		}
		if(itr->entityNo == SKELETON)
		{
			Enemy e(Skeleton, itr->x, itr->y);
			enemylist.push_back(e);
		}
		if(itr->entityNo == TROLL_ARCHER)
		{
			Enemy e(TrollArcher, itr->x, itr->y);
			enemylist.push_back(e);
		}
	}
	
}

void Level::recalculate(int radius)
{
	int x=player->x,y=player->y;
	for(int i=x-radius;i<x+radius;i++)
	{
		for(int j=y-radius;j<y+radius;j++)
		{
			if(i>=0&&i<map->height&&j>=0&&j<map->width&&dist(i,j,x,y)<radius)
			{
				seen[i][j]=4;
			}
		}
	}
	for(int i=x-radius-5;i<x+radius+5;i++)
	{
		for(int j=y-radius-5;j<y+radius+5;j++)
		{
			if(i>=0&&i<map->height&&j>=0&&j<map->width
				&&dist(i,j,x,y)<radius+5&&seen[i][j]==2)
			{
				seen[i][j]=1;
			}
		}
	}
	for(int i=x-radius;i<x+radius;i++)
	{
		for(int j=y-radius;j<y+radius;j++)
		{
			if(i>=0&&i<map->height&&j>=0&&j<map->width&&dist(i,j,x,y)<radius)
			{
				seen[i][j]=2;
			}
		}
	}
	for(int i=0;i<enemylist.size();i++)
	{
		if(dist(enemylist[i].x,enemylist[i].y,x,y)<radius+2)
			enemylist[i].active=true;
	}

}

int Level::dist(int i,int j,int x,int y)
{
	return(abs(i-x)+abs(j-y));
}