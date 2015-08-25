

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
	inPrison = true;
	gameStart = true;
	sprite->setTexture(*txt, true);
	if (clr == "Red"){
		textureBox = new sf::IntRect(456, 64, 16, 16); //left, top , width, height, 456 is start of spritesheet
		this->sprite->setPosition(264, 252.5f);
		this->inPrison = false;
		this->gameStart = false;
	}
	else if (clr == "Pink"){
		textureBox = new sf::IntRect(456, 80, 16, 16); //left, top , width, height, 456 is start of spritesheet
		this->sprite->setPosition(280, 299.525f);
	}
	else if (clr == "Teal"){
		textureBox = new sf::IntRect(456, 96, 16, 16); //left, top , width, height, 456 is start of spritesheet
		this->sprite->setPosition(288, 299.525f);
	}
	else if (clr == "Orange"){
		textureBox = new sf::IntRect(456, 112, 16, 16); //left, top , width, height, 456 is start of spritesheet
		this->sprite->setPosition(285, 299.525f);
	}
	sprite->setTextureRect(*textureBox);
	sprite->setScale(GLOBAL_SCALE, GLOBAL_SCALE);
	//sprite->setPosition(204 * GLOBAL_SCALE, 4 * GLOBAL_SCALE);
	center = new sf::Vector2i();
	center->x = rint(sprite->getPosition().x + sprite->getGlobalBounds().width / 2);
	center->y = rint(sprite->getPosition().y + sprite->getGlobalBounds().height / 2);
	tile = new sf::Vector2i();
	tile->x = floor(((center->x) / (8 * GLOBAL_SCALE)));
	tile->y = floor(((center->y) / (8 * GLOBAL_SCALE)));
	//cout << this->checkGhostPosition().x << " " << this->checkGhostPosition().y << endl;
	target = new sf::Vector2i();
	target->x = 0;
	target->y = 0;

	forwardTileArray = new int[4];
	for (int i = 0; i < 4; i++){
		forwardTileArray[i] = 1;
	}
	level = lvl;
	deadClock = new sf::Clock();
	
}

void Ghost::resetGhost(){
	this->gameStart = true;
	this->inPrison = true;
	if (this->color == "Red"){
		this->getSprite()->setPosition(264, 252.5f);
		this->inPrison = false;
		this->gameStart = false;
	}
	else if (this->color == "Teal"){
		this->sprite->setPosition(288, 299.525f);
	}
	else if (this->color == "Pink"){
		this->sprite->setPosition(280, 299.525f);
	}
	else if (this->color == "Orange"){
		this->sprite->setPosition(285, 299.525f);
	}
	this->direction = 90;
	this->isDead = false;
	this->isScared = false;
	this->isScatter = false;
	this->deadClock->restart();
	center->x = rint(sprite->getPosition().x + sprite->getGlobalBounds().width / 2);
	center->y = rint(sprite->getPosition().y + sprite->getGlobalBounds().height / 2);
	tile->x = floor(((center->x) / (8 * GLOBAL_SCALE)));
	tile->y = floor(((center->y) / (8 * GLOBAL_SCALE)));
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

void Ghost::setLevel(Level* lvl){
	this->level = lvl;
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

void Ghost::togglePanic(){
	if (this->isScared == true){
		this->isScared = false;
	}
	else{
		this->isScared = true;
	}
}

void Ghost::playAnimation(Player* pman, sf::Clock* clk){
	//456, 64 for red
	if (this->isDead){ //if eaten by pacman
		this->textureBox->top = 80;
		if (this->direction == 0){
			this->textureBox->left = 616;
		}
		else if (this->direction == 90){
			this->textureBox->left = 584;
		}
		else if (this->direction == 180){
			this->textureBox->left = 632;
		}
		else{
			this->textureBox->left = 600;
		}
	}
	else{
		if (pman->checkGodStatus()){ //if pacman is invincible
			if (pman->godClock->getElapsedTime().asSeconds() > 5){
				this->textureBox->top = 64;
				this->textureBox->left = 584 + (32 * this->aniFrame);
			}
			else{
				this->textureBox->top = 64;
				this->textureBox->left = 584 + (16 * this->aniFrame);
			}
		}
		else{
			if (this->color == "Red"){
				this->textureBox->top = 64;
			}
			else if (this->color == "Pink"){
				this->textureBox->top = 80;
			}
			else if (this->color == "Orange"){
				this->textureBox->top = 112;
			}
			else{
				this->textureBox->top = 96;
			}
			if (this->direction == 0){
				//if (this->color == "Red"){
				this->textureBox->left = 520 + (16 * this->aniFrame);
				//}

			}
			else if (this->direction == 90){
				this->textureBox->left = 456 + (16 * this->aniFrame);

			}
			else if (this->direction == 180){
				this->textureBox->left = 552 + (16 * this->aniFrame);

			}
			else{ //dir == 270
				this->textureBox->left = 488 + (16 * this->aniFrame);
			}
		}
	}
	this->getSprite()->setTextureRect(*(this->textureBox));
	(this->aniFrame)++;
	if(this->aniFrame == 2){
		this->aniFrame = 0;
	}
}

void Ghost::moveGhost(sf::Clock* clk, Player* pman, Level* lvl, Ghost* redGhost){
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
				if (this->isScatter){
					if (this->isScared == false){
						this->target->x = 27;
						this->target->y = 1;
					}
				}
				if (this->isScared){
					tempTarget = this->findRandomTarget();
					this->target->x = tempTarget.x;
					this->target->y = tempTarget.y;
				}

				//cout << "inside move ghost after findRedTarget" << endl;
				//cout << target->x << " " << target->y << endl;
			}
			else if (this->color == "Pink"){
				sf::Vector2i tempTarget = (this->findPinkTarget(pman));
				//this->target = (this->findRedTarget(pman));
				this->target->x = tempTarget.x;
				this->target->y = tempTarget.y;
				if (this->isScatter){
					this->target->x = 1;
					this->target->y = 1;
				}
				//this->target = &(this->findPinkTarget(pman));
				//cout << "inside move ghost after findPinkTarget" << endl;
				//cout << target->x << " " << target->y << endl;
			}
			else if (this->color == "Teal"){
				sf::Vector2i tempTarget = (this->findTealTarget(pman, redGhost));
				//this->target = (this->findRedTarget(pman));
				this->target->x = tempTarget.x;
				this->target->y = tempTarget.y;
				if (this->isScatter){
					this->target->x = 27;
					this->target->y = 31;
				}
			}
			else if (this->color == "Orange"){
				sf::Vector2i tempTarget = (this->findOrangeTarget(pman));
				//this->target = (this->findRedTarget(pman));
				this->target->x = tempTarget.x;
				this->target->y = tempTarget.y;
				if (this->isScatter){
					this->target->x = 1;
					this->target->y = 31;
				}
			}
			if (this->isDead){
				this->target->x = 11;
				this->target->y = 14;
			}
			this->direction = findShortestpath(lvl);
		}
		this->checkForwardPosition();
	}
	int direction = this->getDirection();
	if (direction == 0){
		this->getSprite()->move(0, -0.016 * this->speed);
	}
	else if (direction == 90){
		this->getSprite()->move(0.016 * this->speed, 0);
	}
	else if (direction == 180){
		this->getSprite()->move(0, 0.016 * this->speed);
	}
	else{
		this->getSprite()->move(-0.016 * this->speed, 0);
	}
	center->x = rint(sprite->getPosition().x + sprite->getGlobalBounds().width / 2);
	center->y = rint(sprite->getPosition().y + sprite->getGlobalBounds().height / 2);
	tile->x = floor(((center->x) / (8 * GLOBAL_SCALE)));
	tile->y = floor(((center->y) / (8 * GLOBAL_SCALE)));
	//handle moving from one side to the other. 
	if (this->tile->y == 13 && this->tile->x == 1){
		this->sprite->setPosition(620.f, 299.525f);
	}
	if (this->tile->y == 13 && this->tile->x == 27){
		this->sprite->setPosition(25.f, 299.525f);
	}
	if (this->isDead){
		//cout << "x " << this->sprite->getPosition().x << " y " << this->sprite->getPosition().y << endl;
		if (this->tile->x == 14 && this->tile->y == 11){
			this->sprite->setPosition(264,299.525f);
			this->deadClock->restart();
			this->isDead = false;
			this->inPrison = true;
		}
	}
	if (this->inPrison){
		if (this->gameStart && this->color == "Orange"){
			if (this->deadClock->getElapsedTime().asSeconds() > 3.f){
				this->sprite->setPosition(264, 252.5f);
				this->direction = 90;
				this->inPrison = false;
				this->gameStart = false;
			}
		}
		else if (this->gameStart && this->color == "Teal"){
			if (this->deadClock->getElapsedTime().asSeconds() > 5.f){
				this->sprite->setPosition(264, 252.5f);
				this->direction = 90;
				this->inPrison = false;
				this->gameStart = false;
			}
		}
		else if (this->gameStart && this->color == "Pink"){
			if (this->deadClock->getElapsedTime().asSeconds() > 7.f){
				this->sprite->setPosition(264, 252.5f);
				this->direction = 270;
				this->inPrison = false;
				this->gameStart = false;
			}
		}
		if (this->color == "Red"){
			cout << this->inPrison << " GS " << this->gameStart << endl;
		}
		if (this->deadClock->getElapsedTime().asSeconds() > 2.f && this->gameStart == false && this->inPrison){
			this->sprite->setPosition(264, 252.5f);
			this->direction = 90;
			this->inPrison = false;
		}
	}
	//cout << this->tile->y
	//11,14 is the top of the box
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
	//cout << "inside red target" << endl;
	return temp;
}

sf::Vector2i Ghost::findPinkTarget(Player* pacman){
	sf::Vector2i tempTarget = pacman->checkPosition();
	//cout << "inside findPinkTarget" << tempTarget.x << " " << tempTarget.y << endl;
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
	if (tempTarget.x > 27){
		tempTarget.x = 27;
	}
	if (tempTarget.y > 31){
		tempTarget.y = 31;
	}
	//cout << "Pinks target is, " << tempTarget.x << " " << tempTarget.y << endl;
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
	//cout << "target in FSP is " << this->target->x << " " << this->target->y << endl;
	//cout << "ghostLocation " << ghostLocation.x << " " << ghostLocation.y << endl;
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

//int Ghost::getDirection(){
	//return this->direction;
//}

sf::Vector2i Ghost::findTealTarget(Player* pman, Ghost* redGhost){
	sf::Vector2i pacLocation = pman->checkPosition();
	sf::Vector2i tempTarget;
	sf::Vector2i redLocation = redGhost->checkGhostPosition();
	if (pman->getDirection() == 0){
		tempTarget.x = pacLocation.x - 2;
		tempTarget.y = pacLocation.y - 2;
	}
	else if (pman->getDirection() == 90){
		tempTarget.x = pacLocation.x + 2;
		tempTarget.y = pacLocation.y;
	}
	else if (pman->getDirection() == 180){
		tempTarget.x = pacLocation.x;
		tempTarget.y = pacLocation.y + 2;
	}
	else{
		tempTarget.x = pacLocation.x - 2;
		tempTarget.y = pacLocation.y;
	}
	sf::Vector2i distance = findTileDistance(tempTarget, redLocation);
	sf::Vector2i target;
	target.x = tempTarget.x + (-1 * distance.x);
	target.y = tempTarget.y + (-1 * distance.y);
	if (target.x < 0){
		target.x = 0;
	}
	if (target.y < 0){
		target.y = 0;
	}
	if (target.x > 27){
		target.x = 27;
	}
	if (target.y > 31){
		target.y = 31;
	}
	//cout << "Teals target is " << target.x << " " << target.y << endl;
	return target;
}

sf::Vector2i Ghost::findOrangeTarget(Player* pman){
	sf::Vector2i pacLocation = pman->checkPosition();
	sf::Vector2i ghostLocation = this->checkGhostPosition();
	sf::Vector2i targetResult;
	double distance = findDistance(&pacLocation, &ghostLocation);
	if (distance >= 8){
		targetResult = pacLocation;
	}
	else{
		targetResult;
		targetResult.x = 1;
		targetResult.y = 31;
	}
	//cout << "Orange's target is " << targetResult.x << " " << targetResult.y << endl;
	return targetResult;
}

sf::Vector2i Ghost::findTileDistance(sf::Vector2i pacTemp, sf::Vector2i ghostPos){
	sf::Vector2i resultVector;
	resultVector.x = ghostPos.x - pacTemp.x;
	resultVector.y = ghostPos.y - pacTemp.y;
	return resultVector;
}

sf::Vector2i Ghost::findRandomTarget(){
	sf::Vector2i tempVector;
	int ranx = rand() % 27 + 1;
	int rany = rand() % 31 + 1;
	tempVector.x = ranx;
	tempVector.y = rany;
	return tempVector;
}

bool Ghost::hasKilledPacman(Player* pman){
	if (this->center->x == pman->getCenter()->x && this->center->y == pman->getCenter()->y){
		if (pman->checkGodStatus()){
			pman->score += 500;
			this->isDead = true;
			return false;
		}
		if (this->isDead){
			return false;
		}
		return true;
	}
	else{
		//cout << "im here" << endl;
		return false;
	}
}

void Ghost::toggleScatter(){
	if (this->isScatter == true){
		this->isScatter = false;
	}
	else{
		this->isScatter = true;
	}
}

void Ghost::resetFTA(){
	this->forwardTileArray[0] = 0;
	this->forwardTileArray[1] = 0;
	this->forwardTileArray[2] = 0;
	this->forwardTileArray[3] = 0;
}

//sf::Vector2i pacLocation = this->checkPosition();
//float delta = clk->restart().asSeconds();
//bool isAtCenter = checkCenter(pacLocation.x, pacLocation.y);
