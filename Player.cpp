#include "Player.h"

Player::Player(sf::Sprite* spr, sf::Texture* txt){
	sprite = spr;
	texture = txt;
	textureBox = new sf::IntRect(456,0,16,16); //left, top , width, height, 456 is start of spritesheet
	sprite->setTextureRect(*textureBox);
	sprite->setScale(3.f, 3.f);
}
sf::Sprite* Player::getSprite(){
	return sprite;
}
void Player::movePlayer(sf::Clock* clk, int direction){
	float delta = clk->restart().asSeconds();
	switch (direction){
	case 0:
		this->sprite->move(0, -(speed * delta));
		break;
	case 90:
		this->sprite->move(speed * delta, 0);
		break;
	case 180:
		this->sprite->move(0, speed * delta);
		break;
	case 270:
		this->sprite->move(-(speed * delta), 0);
		break;
	default:
		return;
	}
}
void Player::setDirection(int dir){
	this->direction = dir;
}

int Player::getDirection(){
	return this->direction;
}
sf::IntRect* Player::getTextureBox(){
	return textureBox;
}
void Player::setRectX(sf::IntRect* rct, int x){
	rct->left = x;
}
void Player::playRun(){
	this->setRectX(this->textureBox, 456 + ((this->aniFrame) * 16) );
	sprite->setTextureRect(*(this->textureBox));
	(this->aniFrame)++;
	if (aniFrame == 2){
		aniFrame = 0;
	}
}