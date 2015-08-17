//Tile* testTile2 = new Tile(tSprite2, pTexture, 16, 8, 200, 0, false); //this is a dot
#include <iostream>
#include <string>
using namespace std;
struct MapTile{
	int sXPos, sYPos, xPos, yPos;
	bool isWall;
};

MapTile* levelOne = new MapTile[1008];
