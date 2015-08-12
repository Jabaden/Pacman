#include "Tile.h"

Tile::Tile(sf::Sprite* spr, sf::Texture* txt, int x, int y, int xPos, int yPos){
	sprite = spr;
	texture = txt;
	textureBox = new sf::IntRect(x, y, 8, 8); //left, top , width, height, 456 is start of pacman spritesheet
	sprite->setTextureRect(*textureBox);
	sprite->setPosition(xPos, yPos);
	sprite->setScale(3.f, 3.f);
}

sf::Sprite* Tile::getSprite(){
	return sprite;
}