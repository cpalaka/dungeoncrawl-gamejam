#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<queue>
#include<vector>
#define BLACK 0
#define WHITE 1
#define WALL 2
#define START 3
#define LADDER 4
#define TREASURE 5
#define BAT 6
#define SKELETON 7
#define TROLL_ARCHER 8
struct entity{
int entityNo;
int x;
int y;
entity(int entityNo,int x,int y)
    {
        this->entityNo=entityNo;
        this->x=x;
        this->y=y;
    }
};
class Map{
    public:
    Map(int height,int width);
	
    int** grid;
    int height;
    int width;
    std::vector<entity> retrieveEntityList();
    void createMap(int percBlack,int firstIterations,int secIterations,int noChests);
    void addMonsters(int noMonsters,int maxMonster,int clusterability,int dispersion);
    void drawMap();
    void applyAutomaton(int born,int dead);

    private:
    void initializeCells(int);
    int countNeighbors(int i,int j,int color);
    void labelComponents();
    void connectedsets(int curr,int x,int y);
    void markWalls();
    void startAndLadder();
    void addChests(int noChests);

    int populateMonsters(int,int,int,int,int);
};
