#include "Tile.h"
#include "GameConfig.h"

Tile::Tile(int xPos, int yPos){
	sprite = new sf::Sprite();
	texture = nullptr;
	textureBox = new sf::IntRect(0, 0, 8, 8);
	this->wall = false;
	center = new sf::Vector2i();
	center->x = rint(xPos + (8 * GLOBAL_SCALE) / 2);
	center->y = rint(yPos + (8 * GLOBAL_SCALE) / 2);
}

Tile::Tile(sf::Sprite* spr, sf::Texture* txt, int x, int y, int xPos, int yPos, bool isWall, bool notEdible){
	sprite = spr;
	texture = txt;
	sprite->setTexture(*txt, true);
	textureBox = new sf::IntRect(x, y, 8, 8); //left, top , width, height, 456 is start of pacman spritesheet
	sprite->setTextureRect(*textureBox);
	sprite->setPosition(xPos, yPos);
	sprite->setScale(GLOBAL_SCALE, GLOBAL_SCALE);
	this->wall = isWall;
	this->isEaten = notEdible;
	this->isBigDot = false;
	center = new sf::Vector2i();
	center->x = rint(xPos + sprite->getGlobalBounds().width / 2);
	center->y = rint(yPos + sprite->getGlobalBounds().height / 2);

}
void Tile::setBlank(){
	this->textureBox->left = 0;
	this->textureBox->top = 80;
	this->getSprite()->setTextureRect(*textureBox);
}

sf::Sprite* Tile::getSprite(){
	return sprite;
}
sf::Vector2i* Tile::getCenter(){
	return center;
}

bool Tile::checkIfEaten(){
	if (this->isEaten){
		return true;
	}
	return false;
}

bool Tile::checkIfBigDot(){
	if (this->isBigDot){
		return true;
	}
	return false;
}

void Tile::eatBigDot(){
	this->isBigDot = false;
}

void Tile::makeBigDot(){
	this->isBigDot = true;
}

bool Tile::getWallStatus(){
	return wall;
}