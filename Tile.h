#include <SFML/Graphics.hpp>

class Tile{
private:
	sf::Sprite* sprite;
	bool isEaten = false;
	bool isPacman = false;
	bool isWall = false;
	sf::Texture* texture;
	sf::IntRect* textureBox;
	//Tile* left;
	//Tile* right;
public:
	Tile(sf::Sprite* spr, sf::Texture* txt, int x = 0, int y = 0, int xPos = 0, int yPos = 0);
	sf::Sprite* getSprite();
};