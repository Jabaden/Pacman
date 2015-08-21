#ifndef GHOST_H
#define GHOST_H

#include <iostream>
#include "Ghost.h"
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
using namespace std;

Ghost::Ghost(sf::Sprite* spr, sf::Texture* txt, Level* lvl, string clr){
	color = clr;
	sprite = spr;
	texture = txt;
	sprite->setTexture(*txt, true);
	if (clr == "Red"){
		textureBox = new sf::IntRect(456, 64, 16, 16); //left, top , width, height, 456 is start of spritesheet
	}
	else if (clr == "Pink"){
		textureBox = new sf::IntRect(456, 80, 16, 16); //left, top , width, height, 456 is start of spritesheet
	}
	sprite->setTextureRect(*textureBox);
	sprite->setScale(GLOBAL_SCALE, GLOBAL_SCALE);
	sprite->setPosition(204 * GLOBAL_SCALE, 4 * GLOBAL_SCALE);
	center = new sf::Vector2i();
	center->x = rint(sprite->getPosition().x + sprite->getGlobalBounds().width / 2);
	center->y = rint(sprite->getPosition().y + sprite->getGlobalBounds().height / 2);
	tile = new sf::Vector2i();
	tile->x = floor(((center->x) / (8 * GLOBAL_SCALE)));
	tile->y = floor(((center->y) / (8 * GLOBAL_SCALE)));
	cout << this->checkGhostPosition().x << " " << this->checkGhostPosition().y << endl;
	target = new sf::Vector2i();
	target->x = 0;
	target->y = 0;

	forwardTileArray = new int[4];
	for (int i = 0; i < 4; i++){
		forwardTileArray[i] = 1;
	}
	level = lvl;
}

sf::Sprite* Ghost::getSprite(){
	return sprite;
}
sf::Vector2i Ghost::checkGhostPosition(){
	return *tile;
}
int Ghost::getDirection(){
	return this->direction;
}

void Ghost::checkForwardPosition(){
	//UP DOWN LEFT RIGHT FOR TILE ARRAY (UP IS THE TOP OF THE GAME BOARD, IT IS INDEPENDANT OF DIRECTION, RIGHT IS ALWAYS RIGHT, ETC)
	this->resetFTA();
	
	sf::Vector2i ghostLocation = this->checkGhostPosition();
	bool isAtCenter = checkCenter(ghostLocation.x, ghostLocation.y);
	if (direction == 0){
		this->forwardTileArray[DOWN] = 1;
		if (level->getLevelMatrix()[((int)ghostLocation.x) + 0][((int)ghostLocation.y) - 1]->getWallStatus() == true){
			this->forwardTileArray[UP] = 1;
		}
		if (level->getLevelMatrix()[((int)ghostLocation.x) - 1][((int)ghostLocation.y) - 1]->getWallStatus() == true){
			this->forwardTileArray[LEFT] = 1;
		}
		if (level->getLevelMatrix()[((int)ghostLocation.x) + 1][((int)ghostLocation.y) - 1]->getWallStatus() == true){
			this->forwardTileArray[RIGHT] = 1;
		}

	}
	else if (direction == 90){
		this->forwardTileArray[LEFT] = 1;

		if (level->getLevelMatrix()[((int)ghostLocation.x) + 1][(int)ghostLocation.y]->getWallStatus() == true){
			this->forwardTileArray[RIGHT] = 1;
		}
		if (level->getLevelMatrix()[((int)ghostLocation.x) + 1][((int)ghostLocation.y) - 1]->getWallStatus() == true){
			this->forwardTileArray[UP] = 1;
		}
		if (level->getLevelMatrix()[((int)ghostLocation.x) + 1][((int)ghostLocation.y) + 1]->getWallStatus() == true){
			this->forwardTileArray[DOWN] = 1;
		}
	}
	else if (direction == 180){
		this->forwardTileArray[UP] = 1;
		if (level->getLevelMatrix()[((int)ghostLocation.x) + 0][((int)ghostLocation.y) + 1]->getWallStatus() == true){
			this->forwardTileArray[DOWN] = 1;
		}
		if (level->getLevelMatrix()[((int)ghostLocation.x) + 1][((int)ghostLocation.y) + 1]->getWallStatus() == true){
			this->forwardTileArray[RIGHT] = 1;
		}
		if (level->getLevelMatrix()[((int)ghostLocation.x) - 1][((int)ghostLocation.y) + 1]->getWallStatus() == true){
			this->forwardTileArray[LEFT] = 1;
		}
	}
	else{
		this->forwardTileArray[RIGHT] = 1;
		if (level->getLevelMatrix()[((int)ghostLocation.x) - 1][((int)ghostLocation.y) - 1]->getWallStatus() == true){
			this->forwardTileArray[UP] = 1;
		}
		if (level->getLevelMatrix()[((int)ghostLocation.x) - 1][((int)ghostLocation.y) + 1]->getWallStatus() == true){
			this->forwardTileArray[DOWN] = 1;
		}
		if (level->getLevelMatrix()[((int)ghostLocation.x) - 1][((int)ghostLocation.y) - 0]->getWallStatus() == true){
			this->forwardTileArray[LEFT] = 1;
		}
	}
}

bool Ghost::checkCenter(int x, int y){
	sf::Vector2i* tileCenter = level->getLevelMatrix()[x][y]->getCenter();
	if (*(this->center) == *tileCenter){
		return true;
	}
	else{
		return false;
	}
}

void Ghost::moveGhost(sf::Clock* clk, Player* pman, Level* lvl){
	//sf::Vector2i pacLocation = this->checkPosition();
	float delta = clk->restart().asSeconds();
	bool isAtCenter = this->checkCenter(this->tile->x, this->tile->y);
	if (isAtCenter){
		//cout << "im at the center" << endl;
		if (this->isIntersection()){
			//cout << "this is an intersection" << endl;
			if (this->color == "Red"){
				sf::Vector2i tempTarget = (this->findRedTarget(pman));
				//this->target = (this->findRedTarget(pman));
				this->target->x = tempTarget.x;
				this->target->y = tempTarget.y;
				//cout << "inside move ghost after findRedTarget" << endl;
				//cout << target->x << " " << target->y << endl;
			}
			else if (this->color == "Pink"){
				sf::Vector2i tempTarget = (this->findPinkTarget(pman));
				//this->target = (this->findRedTarget(pman));
				this->target->x = tempTarget.x;
				this->target->y = tempTarget.y;
				//this->target = &(this->findPinkTarget(pman));
				//cout << "inside move ghost after findPinkTarget" << endl;
				//cout << target->x << " " << target->y << endl;
			}
			this->direction = findShortestpath(lvl);
		}
		this->checkForwardPosition();
	}
	int direction = this->getDirection();
	if (direction == 0){
		this->getSprite()->move(0, -delta * this->speed);
	}
	else if (direction == 90){
		this->getSprite()->move(delta * this->speed, 0);
	}
	else if (direction == 180){
		this->getSprite()->move(0, delta * this->speed);
	}
	else{
		this->getSprite()->move(-delta * this->speed, 0);
	}
	center->x = rint(sprite->getPosition().x + sprite->getGlobalBounds().width / 2);
	center->y = rint(sprite->getPosition().y + sprite->getGlobalBounds().height / 2);
	tile->x = floor(((center->x) / (8 * GLOBAL_SCALE)));
	tile->y = floor(((center->y) / (8 * GLOBAL_SCALE)));
}

bool Ghost::isIntersection(){
	int amount = 0;
	for (int i = 0; i < 4; i++){
		if (this->forwardTileArray[i] == 0){
			amount++;
		}
	}
	return amount > 1 ? true : false;
}

sf::Vector2i Ghost::findRedTarget(Player* pacman){
	sf::Vector2i temp = pacman->checkPosition();
	//cout << "inside findRedTarget" << temp.x << " " << temp.y << endl;
	//return pacman->checkPosition();
	return temp;
}

sf::Vector2i Ghost::findPinkTarget(Player* pacman){
	sf::Vector2i tempTarget = pacman->checkPosition();
	cout << "inside findPinkTarget" << tempTarget.x << " " << tempTarget.y << endl;
	if (pacman->getDirection() == 0){
		tempTarget.x = tempTarget.x - 4; //this is a strange exception in the games code
		tempTarget.y = tempTarget.y - 4; 
	}
	else if (pacman->getDirection() == 90){
		tempTarget.x = tempTarget.x + 4;
	}
	else if (pacman->getDirection() == 180){
		tempTarget.y = tempTarget.y + 4;
	}
	else{
		tempTarget.x = tempTarget.x - 4;
	}
	if (tempTarget.x < 0){
		tempTarget.x = 0;
	}
	if (tempTarget.y < 0){
		tempTarget.y = 0;
	}
	cout << "Pinks target is, " << tempTarget.x << " " << tempTarget.y << endl;
	return tempTarget;
}

int Ghost::findShortestpath(Level* lvl){
	int dir = this->direction;
	int upShortest = 0;
	int downShortest = 180;
	int rightShortest = 90;
	int leftShortest = 270;
	double distance = 0;
	double shortestDistance = 10000000;
	double returnDistance = 0;
	sf::Vector2i* tileCenter;
	sf::Vector2i ghostLocation = this->checkGhostPosition();
	cout << "target in FSP is " << this->target->x << " " << this->target->y << endl;
	cout << "ghostLocation " << ghostLocation.x << " " << ghostLocation.y << endl;
	sf::Vector2i* targetCenter = (lvl->getLevelMatrix()[this->target->x][this->target->y]->getCenter());
	if (dir != 180){ //check up
		if (level->getLevelMatrix()[((int)ghostLocation.x) + 0][((int)ghostLocation.y) - 1]->getWallStatus() == false){
			tileCenter = level->getLevelMatrix()[((int)ghostLocation.x) + 0][((int)ghostLocation.y) - 1]->getCenter();
			distance = findDistance(tileCenter, targetCenter);
			if (distance < shortestDistance){
				shortestDistance = distance;
				returnDistance = upShortest;
			}
		}
	}
	if (dir != 0){//check down
		if (level->getLevelMatrix()[((int)ghostLocation.x) + 0][((int)ghostLocation.y) + 1]->getWallStatus() == false){
			tileCenter = level->getLevelMatrix()[((int)ghostLocation.x) + 0][((int)ghostLocation.y) + 1]->getCenter();
			distance = findDistance(tileCenter, targetCenter);
			if (distance < shortestDistance){
				shortestDistance = distance;
				returnDistance = downShortest;
			}
		}
	}
	if (dir != 90){//check left
		if (level->getLevelMatrix()[((int)ghostLocation.x) - 1][((int)ghostLocation.y) + 0]->getWallStatus() == false){
			tileCenter = level->getLevelMatrix()[((int)ghostLocation.x) - 1][((int)ghostLocation.y) + 0]->getCenter();
			distance = findDistance(tileCenter, targetCenter);
			if (distance < shortestDistance){
				shortestDistance = distance;
				returnDistance = leftShortest;
			}
		}
	}
	if (dir != 270){//check right
		if (level->getLevelMatrix()[((int)ghostLocation.x) + 1][((int)ghostLocation.y) + 0]->getWallStatus() == false){
			tileCenter = level->getLevelMatrix()[((int)ghostLocation.x) + 1][((int)ghostLocation.y) + 0]->getCenter();
			distance = findDistance(tileCenter, targetCenter);
			if (distance < shortestDistance){
				shortestDistance = distance;
				returnDistance = rightShortest;
			}
		}
	}
	return returnDistance; //should be either 0, 90, 180, 270
}

double Ghost::findDistance(sf::Vector2i* ghostCenter, sf::Vector2i* targetCenter){ //returns the distance between two points
	/*
	double Distance(double dX0, double dY0, double dX1, double dY1)
	{
	return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
	}
	*/
	return sqrt((targetCenter->x - ghostCenter->x) * (targetCenter->x - ghostCenter->x) + (targetCenter->y - ghostCenter->y) * (targetCenter->y - ghostCenter->y));
}

void Ghost::resetFTA(){
	this->forwardTileArray[0] = 0;
	this->forwardTileArray[1] = 0;
	this->forwardTileArray[2] = 0;
	this->forwardTileArray[3] = 0;
}

#endif
//sf::Vector2i pacLocation = this->checkPosition();
//float delta = clk->restart().asSeconds();
//bool isAtCenter = checkCenter(pacLocation.x, pacLocation.y);