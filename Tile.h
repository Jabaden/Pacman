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
	bool isBigDot = false;
	sf::Texture* texture;
	sf::IntRect* textureBox;
	

public:
	Tile(int xPos, int yPos);
	Tile(sf::Sprite* spr, sf::Texture* txt, int x, int y, int xPos, int yPos, bool isWall, bool edible);
	sf::Sprite* getSprite();
	sf::Vector2i* getCenter();
	bool getWallStatus();
	sf::Vector2i* center;
	void setBlank();
	void eatBigDot();
	void makeBigDot();
	bool checkIfEaten();
	bool checkIfBigDot();
	bool canScore = true;
};
#endif