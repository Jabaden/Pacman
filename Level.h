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
	Tile*** copyMatrix;
public:
	int dots = 0;
	Level(fstream& levelFile, sf::Texture* txt, int level);
	Tile*** getLevelMatrix();
	void setTile(int x, int y, Tile* tile);
	void renderLevel(sf::RenderWindow* wnd);
	void resetLevel(fstream&, sf::Texture* txt, int level);
};
#endif