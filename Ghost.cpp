#include "Ghost.h"

Ghost::Ghost(sf::Sprite* spr, sf::Texture* txt){
	sprite = spr;
	texture = txt;
	sprite->setTexture(*txt, true);
	textureBox = new sf::IntRect(456, 64, 16, 16); //left, top , width, height, 456 is start of spritesheet
	sprite->setTextureRect(*textureBox);
	//sprite->setScale(3.f, 3.f);
	sprite->setPosition(144, 144);
	sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
	center = sprite->getOrigin();
}

sf::Sprite* Ghost::getSprite(){
	return sprite;
}