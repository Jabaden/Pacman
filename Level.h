#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "Tile.h"

#define GameWidth 672
#define GameHeight 864

using namespace std;
class Level{
private:
	Tile*** levelMatrix;
public:
	Level(fstream& levelFile);
	Tile*** getLevelMatrix();
	void setTile(int x, int y, Tile* tile);
	void renderLevel(sf::RenderWindow* wnd);
};
#endif