#ifndef GHOST_H
#define GHOST_H
#include "Tile.h"
#include "Player.h"
#include "GameConfig.h"
#include "Level.h"
class Ghost{
private:
	sf::Sprite* sprite;
	sf::Texture* texture;
	int direction = 270;
	float speed = 1.75f;
	sf::IntRect* textureBox;
	int aniFrame = 0;
	sf::Vector2i* tile;
	sf::Vector2i* center;
	int* forwardTileArray; //up down left right, 1 = wall, 0 = free tiles
	Level* level;
	sf::Vector2i* target;
	sf::Vector2i* scatterTarget;
	string color = "black";
	
	
public:
	Ghost(sf::Sprite* spr, sf::Texture* txt, Level* lvl, string clr);
	sf::Sprite* getSprite();
	sf::Vector2i checkGhostPosition();
	void checkForwardPosition();
	bool checkCenter(int x, int y);
	void resetFTA();
	void moveGhost(sf::Clock* clk, Player* pman, Level* lvl, Ghost* redGhost);
	void toggleScatter();
	void togglePanic();
	void resetGhost();
	void setLevel(Level* lvl);
	sf::Vector2i findRedTarget(Player* pacman);
	sf::Vector2i findOrangeTarget(Player* pacman);
	sf::Vector2i findPinkTarget(Player* pacman);
	sf::Vector2i findTealTarget(Player* pman, Ghost* redGhost);
	bool isIntersection();
	bool hasKilledPacman(Player* pman);
	int getDirection();
	int findShortestpath(Level* lvl);
	sf::Vector2i findRandomTarget();
	void playAnimation(Player* pman, sf::Clock* clk);
	double findDistance(sf::Vector2i* ghostCenter, sf::Vector2i* targetCenter);
	sf::Vector2i findTileDistance(sf::Vector2i pacTemp, sf::Vector2i ghostPos);
	sf::Clock* deadClock;
	bool isDead = false;
	bool isScatter = false;
	bool isScared = false;
	bool inPrison = true;
	bool gameStart = true;
};
#endif