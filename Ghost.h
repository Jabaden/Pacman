#include "Tile.h"
class Ghost{
private:
	Tile* target;
	sf::Sprite* sprite;
	sf::Texture* texture;
	int direction = 90;
	float speed = 80.f;
	sf::IntRect* textureBox;
	int aniFrame = 0;
	sf::Vector2f center;
public:
	Ghost(sf::Sprite* spr, sf::Texture* txt);
	sf::Sprite* getSprite();
};