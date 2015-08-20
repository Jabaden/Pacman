#include "Player.h"

Player::Player(sf::Sprite* spr, sf::Texture* txt, Level* lvl){
	sprite = spr;
	texture = txt;
	textureBox = new sf::IntRect(456,0,16,16); //left, top , width, height, 456 is start of spritesheet
	sprite->setTextureRect(*textureBox);
	sprite->setScale(GLOBAL_SCALE, GLOBAL_SCALE);
	sprite->setPosition(4 * GLOBAL_SCALE, 4 * GLOBAL_SCALE); //was -4, -4
	//sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
	center = new sf::Vector2i();
	center->x = rint(sprite->getPosition().x + sprite->getGlobalBounds().width / 2);
	center->y = rint(sprite->getPosition().y + sprite->getGlobalBounds().height / 2);
	
	tile = new sf::Vector2i();
	tile->x = floor(((center->x) / (8 * GLOBAL_SCALE)));
	tile->y = floor(((center->y) / (8 * GLOBAL_SCALE)));
	level = lvl;

}
sf::Sprite* Player::getSprite(){
	return sprite;
}
void Player::movePlayer(sf::Clock* clk, int direction){

	sf::Vector2i pacLocation = this->checkPosition();
	float delta = clk->restart().asSeconds();
	bool isAtCenter = checkCenter(pacLocation.x, pacLocation.y);
	switch (direction){
	case 0: //up
		if (isAtCenter){
			if (level->getLevelMatrix()[(int)pacLocation.x][((int)pacLocation.y) - 1]->getWallStatus() == true){
				upDown = false;
				leftRight = false;
				return;
			}
		}
		this->sprite->move(0, -(speed * delta));
		break;
	case 90:
		if (isAtCenter){
			if (level->getLevelMatrix()[((int)pacLocation.x) + 1][(int)pacLocation.y]->getWallStatus() == true){
				upDown = false;
				leftRight = false;
				return;
			}
		}
		this->sprite->move(speed * delta, 0);
		break;
	case 180:
		if (isAtCenter){
			if (level->getLevelMatrix()[(int)pacLocation.x][((int)pacLocation.y) + 1]->getWallStatus() == true){
				upDown = false;
				leftRight = false;
				return;
			}
		}
		this->sprite->move(0, speed * delta);
		break;
	case 270:
		if (isAtCenter){
			if (level->getLevelMatrix()[((int)pacLocation.x) - 1][(int)pacLocation.y]->getWallStatus() == true){
				upDown = false;
				leftRight = false;
				return;
			}
		}
		this->sprite->move(-(speed * delta), 0);
		break;
	}
	center->x = rint(sprite->getPosition().x + sprite->getGlobalBounds().width / 2);
	center->y = rint(sprite->getPosition().y + sprite->getGlobalBounds().height / 2);
	tile->x = floor(((center->x) / (8 * GLOBAL_SCALE)));
	tile->y = floor(((center->y) / (8 * GLOBAL_SCALE)));
	//cout << "tilex is " << tile->x << " and tiley is " << tile->y << endl;
	//cout << "the center of tile [1][2] is " << level->getLevelMatrix()[0][0]->getCenter()->x << " " << level->getLevelMatrix()[0][0]->getCenter()->y << endl;
	//cout << "the center of my tile is" << level->getLevelMatrix()[tile->x][tile->y]->center->x << ", " << level->getLevelMatrix()[tile->x][tile->y]->center->y << endl;
	//cout << "the center of pacman is " << this->center->x << " " << this->center->y << endl;
	//cout << "the center of my tile is" << level->getLevelMatrix()[tile->x][tile->y]->center->x << ", " << level->getLevelMatrix()[tile->x][tile->y]->center->y << endl;
}
void Player::setDirection(int dir){
	sf::Vector2i pacLocation = this->checkPosition();
	bool isAtCenter = this->checkCenter(pacLocation.x, pacLocation.y);
	bool canTurn = ((leftRight && (dir == 270 || dir == 90)) || (upDown && (dir == 0 || dir == 180)));
	if (!isAtCenter && !canTurn){
		return;
	}
	if (dir == 270 || dir == 90){
		//if (dir == 90){
			//if (level->getLevelMatrix()[((int)pacLocation.x) + 1][(int)pacLocation.y]->getWallStatus() == true){
				//return;
			//}
		//}
		//else{
			//if (level->getLevelMatrix()[((int)pacLocation.x) - 1][(int)pacLocation.y]->getWallStatus() == true){
				//return;
			//}
		//}
		leftRight = true;
		upDown = false;
	}
	else{
		//if (dir == 0){
			//if (level->getLevelMatrix()[(int)pacLocation.x][((int)pacLocation.y) - 1]->getWallStatus() == true){
				//return;
			//}
		//}
		//else{
			//if (level->getLevelMatrix()[(int)pacLocation.x][((int)pacLocation.y) + 1]->getWallStatus() == true){
				//return;
			//}
		//}
		leftRight = false;
		upDown = true;
	}
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

void Player::setRectY(sf::IntRect* rct, int y){
	rct->top = y;
}

void Player::playRun(){
	
	if (direction == 90){
		this->setRectY(this->textureBox, 0); // row 1
		this->setRectX(this->textureBox, 456 + ((this->aniFrame) * 16));
		sprite->setTextureRect(*(this->textureBox));
		(this->aniFrame)++;
		if (aniFrame == 2){
			aniFrame = 0;
		}
	}
	else if (direction == 180){
		this->setRectY(this->textureBox, 48); // row 4
		this->setRectX(this->textureBox, 456 + ((this->aniFrame) * 16));
		sprite->setTextureRect(*(this->textureBox));
		(this->aniFrame)++;
		if (aniFrame == 2){
			aniFrame = 0;
		}
	}
	else if (direction == 270){
		this->setRectY(this->textureBox, 16); // row 4
		this->setRectX(this->textureBox, 456 + ((this->aniFrame) * 16));
		sprite->setTextureRect(*(this->textureBox));
		(this->aniFrame)++;
		if (aniFrame == 2){
			aniFrame = 0;
		}
	}
	else{
		this->setRectY(this->textureBox, 32); // row 4
		this->setRectX(this->textureBox, 456 + ((this->aniFrame) * 16));
		sprite->setTextureRect(*(this->textureBox));
		(this->aniFrame)++;
		if (aniFrame == 2){
			aniFrame = 0;
		}
	}
}

void Player::playDeath(){
	this->setRectY(this->textureBox, 0);
	this->setRectX(this->textureBox, 488 + ((this->aniFrame) * 16));
	sprite->setTextureRect(*(this->textureBox));
	(this->aniFrame)++;
	if (aniFrame > 12){
		aniFrame = 12;
	}
}

sf::Vector2i Player::checkPosition(){
	return *tile;
}

sf::Vector2i Player::checkPosition(sf::RenderWindow* wnd){
	//sf::Vector2i test;
	//float xCoord = floor(((this->getSprite()->getPosition().x)/24));
	//float yCoord = floor(((this->getSprite()->getPosition().y) / 24));
	float xCoord = center->x;
	float yCoord = center->y;
	std::string newTitle = "";
	std::string xString = std::to_string(xCoord);
	std::string yString = std::to_string(yCoord);
	newTitle += xString;
	newTitle += " and ";
	newTitle += yString;

	sf::Vector2i testTwo = this->checkPosition();
	newTitle += " and ";
	sf::Vector2i* tileCenter = level->getLevelMatrix()[(int)testTwo.x][(int)testTwo.y]->getCenter();
//	newTitle += ((int)(center->x) == (int)(tileCenter->x) && (int)(center->y) == (int)(tileCenter->y)) ? "true" : "false";
	newTitle += std::to_string(checkCenter(testTwo.x, testTwo.y));
	newTitle += " and ";
	newTitle += std::to_string(tileCenter->x);
	newTitle += " and ";
	newTitle += std::to_string(tileCenter->y);
	newTitle += std::to_string((int)tileCenter);
	wnd->setTitle(newTitle);
	sf::Vector2f tempPair(xCoord, yCoord);

	return checkPosition();
}

bool Player::checkCenter(int x, int y){
	//cout << "x is " << x << " y is " << y << endl;
	sf::Vector2i* tileCenter = level->getLevelMatrix()[x][y]->getCenter();
	//cout << "the center of pacman is " << this->center->x << " " << this->center->y << endl;
	//cout << "The center of the tile is " << tileCenter->x << " " << tileCenter->y << endl;
	if (*(this->center) == *tileCenter){
		return true;
	}
	else{
		return false;
	}

}