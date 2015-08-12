#include "Tile.h"
class Ghost{
private:
	Tile* target;
	sf::Sprite* sprite;
	sf::Texture* texture;
	int direction = 90;
	sf::IntRect* textureBox;
public:
	Ghost();
};