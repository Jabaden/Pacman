#include <SFML/Graphics.hpp>
class Player{
private:
	sf::Sprite* sprite;
	sf::Texture* texture;
	float speed = 80.f;
	int direction = 90;
	sf::IntRect* textureBox;
	int aniFrame = 0;
	sf::Vector2f center;

public:
	Player(sf::Sprite* spr, sf::Texture* txt);
	sf::Sprite* getSprite();
	void movePlayer(sf::Clock* clk, int direction);//0 is up, 90 is right etc.
	int getDirection();

	void setDirection(int dir);
	void setRectX(sf::IntRect* rct, int x);
	void setRectY(sf::IntRect* rct, int y);

	sf::IntRect* getTextureBox();

	void playRun();
	void playDeath();

};