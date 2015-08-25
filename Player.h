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
	float speed = 2.f;
	int direction = 90;
	bool isGod = false;
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
	void toggleGod();

	sf::IntRect* getTextureBox();

	void playRun();
	void playDeath();
	sf::Vector2i checkPosition();
	sf::Vector2i checkPosition(sf::RenderWindow* wnd);
	sf::Vector2i* getCenter();
	bool checkCenter(int x, int y);
	bool checkGodStatus();
	bool leftRight = false;
	bool upDown = false;
	sf::Clock* godClock;
	sf::Clock* restartClock;
	bool isDead = false;
	void restartPacman();
	void setLevel(Level* lvl);
	int dotsLeft = 1000;
	int score = 0;
	
};
#endif