#include "Map.h"
Map::Map(int height,int width)
    {
    this->height=height;
    this->width=width;

    grid=new int*[height];

	for(int i=0;i<height;i++)
	{
        grid[i]=new int[width];
    }

}

void Map::initializeCells(int percBlack)
{
    srand(time(0));
    for(int i=0;i<this->height;i++)
    {
        for(int j=0;j<this->width;j++)
        {
            grid[i][j]=rand()%100>percBlack;
        }
    }
}

int Map::countNeighbors(int i,int j,int color)
{
                int count=0;
                int arrX[]={-1,-1,-1,0,0,1,1,1},arrY[]={-1,0,1,-1,1,-1,0,1};
                    for(int x=0;x<8;x++)
                    {
                        if(i+arrX[x]>=0&&i+arrX[x]<this->height
                        &&j+arrY[x]>=0&&j+arrY[x]<this->width
                        &&grid[i+arrX[x]][j+arrY[x]]==color)
                        count++;
                    }
                return count;
}

void Map::applyAutomaton(int born,int dead)
{
    for(int i=0;i<this->height;i++)
    {
        for(int j=0;j<this->width;j++)
        {
            if(i==0||i==this->height-1||j==0||j==this->width-1)
            {
                grid[i][j]=BLACK;
            }
            else if(grid[i][j]==BLACK)
            {
               if(countNeighbors(i,j,WHITE)>=born)
               {
                        grid[i][j]=WHITE;//BORN!
                }
            }
            else if(grid[i][j]==WHITE)
            {
                if(countNeighbors(i,j,WHITE)<dead)
                {
                    grid[i][j]=BLACK;//DEAD
                }
            }
        }
    }
}

void Map::createMap(int percBlack=45,int firstIteration=4,int secIteration=4,int noChests=10)
{
    this->initializeCells(percBlack);
    for(int i=0;i<firstIteration;i++)
        this->applyAutomaton(6,3);
    for(int i=0;i<secIteration;i++)
        this->applyAutomaton(5,4);
    this->labelComponents();
    this->markWalls();
    this->startAndLadder();
    this->addChests(noChests);
    //this->addMonsters(40,TROLL,20,50);
    
}

void Map::markWalls()
{
    for(int i=0;i<this->height;i++)
        for(int j=0;j<this->width;j++)
            if(grid[i][j]==BLACK&&countNeighbors(i,j,WHITE)>0)
                grid[i][j]=WALL;
}

void Map::drawMap()
{
int countBlack=0,countWhite=0;
for(int i=0;i<this->height;i++)
{
    for(int j=0;j<this->width;j++)
    {
		std::cout<<grid[i][j];
        if(grid[i][j]==BLACK)
            countBlack++;
        else
            countWhite++;
    }

	std::cout<<std::endl;
}
}

void Map::labelComponents()
{
    int curr=2;
    for(int i=0;i<this->height;i++)
    {
        for(int j=0;j<this->width;j++)
        {
            if(grid[i][j]==1)
            {
                connectedsets(curr,i,j);
                curr++;
            }
        }
    }
    int* counts=new int[curr]();
    for(int i=0;i<this->height;i++)
        for(int j=0;j<this->width;j++)
            if(grid[i][j]!=0)
                counts[ grid[i][j]]++;
    int max=0,maxpixel=0;
    for(int i=0;i<curr;i++)
        if(counts[i]>max)
        {
            maxpixel=i;
            max=counts[i];
        }
    for(int i=0;i<this->height;i++)
        for(int j=0;j<this->width;j++)
            if(grid[i][j]==maxpixel)
                grid[i][j]=WHITE;
            else
                grid[i][j]=BLACK;
}

void Map::connectedsets(int curr,int x,int y)
{
    std::queue<std::pair<int,int> > q;
    q.push(std::make_pair(x,y));
    while(!q.empty())
    {
    std::pair<int,int> p=q.front();
    q.pop();
    if(p.first>=0&&p.first<this->height&p.second>=0&&p.second<this->width)
        if(grid[p.first][p.second]==1)
        {
            grid[p.first][p.second]=curr;
            q.push(std::make_pair(p.first-1,p.second));
            q.push(std::make_pair(p.first+1,p.second));
            q.push(std::make_pair(p.first,p.second-1));
            q.push(std::make_pair(p.first,p.second+1));
        }
    }
}

void Map::startAndLadder()
{
    int arrX[]={0,this->height-1,this->height-1,0},arrY[]={0,0,this->width-1,this->width-1};
    bool found=false;
    bool** visited=new bool*[this->height];
    for(int i=0;i<this->height;i++)
        visited[i]=new bool[this->width]();
    std::queue<std::pair<int,int> > q;
    srand(time(0));
    int x=rand()%4;
    q.push(std::make_pair(arrX[x],arrY[x]));
    int startX=0,startY=0,ladderX=0,ladderY=0;
    visited[arrX[x]][arrY[x]]=true;
    while(!found)
    {
        std::pair<int,int> p=q.front();
        q.pop();
        if(countNeighbors(p.first,p.second,WHITE)==8)
        {
            found==true;
            startX=p.first;
            startY=p.second;
            while(!q.empty())
                q.pop();
            break;
        }
        else
        {
                    int arrX[]={-1,-1,-1,0,0,1,1,1},arrY[]={-1,0,1,-1,1,-1,0,1};
                    for(int x=0;x<8;x++)
                    {
                        if(p.first+arrX[x]>=0&&p.first+arrX[x]<this->height
                        &&p.second+arrY[x]>=0&&p.second+arrY[x]<this->width
                        &&!visited[p.first+arrX[x]][p.second+arrY[x]])
                        {
                            visited[p.first+arrX[x]][p.second+arrY[x]]=true;
                            q.push(std::make_pair(p.first+arrX[x],p.second+arrY[x]));
                        }
                    }
        }
    }

    x=(x+1+rand()%3)%4;
    for(int i=0;i<this->height;i++)
        for(int j=0;j<this->width;j++)
            visited[i][j]=false;
    found=false;
    q.push(std::make_pair(arrX[x],arrY[x]));
    visited[arrX[x]][arrY[x]]=true;
    while(!found)
    {
        std::pair<int,int> p=q.front();
        q.pop();
        if(countNeighbors(p.first,p.second,WHITE)==8)
        {
            found==true;
            ladderX=p.first;
            ladderY=p.second;
            break;
        }
        else
        {
                    int arrX[]={-1,-1,-1,0,0,1,1,1},arrY[]={-1,0,1,-1,1,-1,0,1};
                    for(int x=0;x<8;x++)
                    {
                        if(p.first+arrX[x]>=0&&p.first+arrX[x]<this->height
                        &&p.second+arrY[x]>=0&&p.second+arrY[x]<this->width
                        &&!visited[p.first+arrX[x]][p.second+arrY[x]])
                        {
                            visited[p.first+arrX[x]][p.second+arrY[x]]=true;
                            q.push(std::make_pair(p.first+arrX[x],p.second+arrY[x]));
                        }
                    }
        }
    }
    grid[startX][startY]=START;
    grid[ladderX][ladderY]=LADDER;
}

void Map::addChests(int noChests)
{
    std::vector<std::pair<int,int> > spots;
    for(int i=0;i<this->height;i++)
    {
        for(int j=0;j<this->width;j++)
        {
            if(countNeighbors(i,j,WALL)==5&&grid[i][j]==WHITE)
                spots.push_back(std::make_pair(i,j));
        }
    }
    std::cout<<spots.size()<<std::endl;
    if(spots.size()<noChests)
    {
    for(int i=0;i<this->height;i++)
    {
        for(int j=0;j<this->width;j++)
        {
            if(countNeighbors(i,j,WALL)==4&&grid[i][j]==WHITE)
                spots.push_back(std::make_pair(i,j));
        }
    }
    }
    srand(time(0));
    int count=0,it=0;
    while(count<noChests)
    {
        if(grid[spots[it%spots.size()].first][spots[it%spots.size()].second]==WHITE&&rand()%spots.size()==0)
        {
            grid[spots[it%spots.size()].first][spots[it%spots.size()].second]=TREASURE;
                count++;
                it+=spots.size()/2;
        }
        it++;
        if(it>1000&&spots.size()<noChests)
            break;
    }
}

void Map::addMonsters(int noMonsters,int maxMonster,int clusterabilty,int dispersion=200)
{
   int count=0,it=0;

   srand(time(0));
   while(count<noMonsters)
   {
        if(countNeighbors(it/this->height,it%this->width,WHITE)==8&&grid[it/this->height][it%this->width]==WHITE)
        {
            if(rand()%dispersion==0)
            {
                count+=populateMonsters(noMonsters-count,maxMonster,clusterabilty,it/this->height,it%this->width);
                if(count>=noMonsters)
                    return;
            }
        }
        it++;
        if(it%1000==0&&dispersion>5)
            dispersion-=5;
        if(it==10000)
            return;
   }
}

int Map::populateMonsters(int noMonsters,int maxMonster,int clusterability,int x,int y)
{
    std::queue<std::pair<int,int> > q;
    grid[x][y]=maxMonster;
    int count=0;
    maxMonster--;
    int arrX[]={-1,0,0,1},arrY[]={0,-1,1,0};
    q.push(std::make_pair(x,y));
    srand(time(0));
    while(!q.empty())
    {
        std::pair<int,int> p=q.front();
        q.pop();
        for(int x=0;x<4;x++)
        {
                        if(p.first+arrX[x]>=0&&p.first+arrX[x]<this->height
                        &&p.second+arrY[x]>=0&&p.second+arrY[x]<this->width
                        &&grid[p.first+arrX[x]][p.second+arrY[x]]==WHITE
                        &&rand()%100<clusterability)
                        {
                            grid[p.first+arrX[x]][p.second+arrY[x]]=maxMonster;
                            q.push(std::make_pair(p.first+arrX[x],p.second+arrY[x]));
                            count++;
							if(count>=noMonsters)
									return count;
                        }
        }
                        maxMonster--;
                        if(maxMonster==BAT-1)
                            return count;
    }
    return count;
}


std::vector<entity> Map::retrieveEntityList()
{
std::vector<entity> ans;
for(int i=0;i<this->height;i++)
{
    for(int j=0;j<this->width;j++)
    {
        if(grid[i][j]>2)
        {
            entity e(grid[i][j],i,j);
            ans.push_back(e);
        }
    }
}
return ans;
}
