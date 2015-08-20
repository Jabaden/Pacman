#include "Tile.h"
#include "Player.h"
#include "GameConfig.h"
#include "Level.h"
class Ghost{
private:
	//Tile* target;
	sf::Sprite* sprite;
	sf::Texture* texture;
	int direction = 270;
	float speed = 20.f;
	sf::IntRect* textureBox;
	int aniFrame = 0;
	sf::Vector2i* tile;
	sf::Vector2i* center;
	int* forwardTileArray; //up down left right, 1 = wall, 0 = free tiles
	Level* level;
	sf::Vector2i* target;
	
public:
	Ghost(sf::Sprite* spr, sf::Texture* txt, Level* lvl);
	sf::Sprite* getSprite();
	sf::Vector2i checkGhostPosition();
	void checkForwardPosition();
	bool checkCenter(int x, int y);
	void resetFTA();
	void moveGhost(sf::Clock* clk, Player* pman, Level* lvl);
	sf::Vector2i findRedTarget(Player* pacman);
	bool isIntersection();
	int getDirection();
	int findShortestpath(Level* lvl);
	double findDistance(sf::Vector2i* ghostCenter, sf::Vector2i* targetCenter);
};