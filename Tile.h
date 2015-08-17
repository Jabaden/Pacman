#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include <math.h>

class Tile{
private:
	sf::Sprite* sprite;
	bool isEaten = false;
	bool isPacman = false;
	bool wall = false;
	bool ghost = true;
	sf::Texture* texture;
	sf::IntRect* textureBox;
	
	//Tile* left;
	//Tile* right;
public:
	Tile(int xPos, int yPos);
	Tile(sf::Sprite* spr, sf::Texture* txt, int x, int y, int xPos, int yPos, bool isWall);
	sf::Sprite* getSprite();
	sf::Vector2i* getCenter();
	bool getWallStatus();
	sf::Vector2i* center;
};
#endif