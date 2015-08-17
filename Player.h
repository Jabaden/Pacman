#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <string>
#include <utility>
#include "Level.h"
#include "GameConfig.h"

class Player{
private:
	sf::Sprite* sprite;
	sf::Texture* texture;
	float speed = 20.f;
	int direction = 90;
	sf::IntRect* textureBox;
	int aniFrame = 0;
	sf::Vector2i* center;
	sf::Vector2i* tile;
	Level* level;
	

public:
	Player(sf::Sprite* spr, sf::Texture* txt, Level* lvl);
	sf::Sprite* getSprite();
	void movePlayer(sf::Clock* clk, int direction);//0 is up, 90 is right etc.
	int getDirection();

	void setDirection(int dir);
	void setRectX(sf::IntRect* rct, int x);
	void setRectY(sf::IntRect* rct, int y);

	sf::IntRect* getTextureBox();

	void playRun();
	void playDeath();
	sf::Vector2i checkPosition();
	sf::Vector2i checkPosition(sf::RenderWindow* wnd);
	bool checkCenter(int x, int y);

	bool leftRight = false;
	bool upDown = false;
	
};
#endif