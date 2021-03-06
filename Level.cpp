#include "level.h"
#include "GameConfig.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

Level::Level(fstream& levelFile, sf::Texture* txt, int level){
	if (level == 1){
		levelFile.open("levelOne.txt");
	}
	if (level == 2){
		levelFile.open("levelTwo.txt");
	}
	string currentLine;
	string sType;
	string sAmount;
	int type = 0; //the type of wall
	int amount = 0; //the number of that wall
	int dLocation = 0;
	int lineNumber = 0;
	int space = 0;
	int row = 0;
	int column = 0;
	int numDots = 0;

	levelMatrix = new Tile**[28];
	for (int i = 0; i < 28; i++){
		levelMatrix[i] = new Tile*[36];
	}

	while (getline(levelFile, currentLine)){
		lineNumber++;
		sType = currentLine.substr(0, 1); //type of wall
		if (sType == "#"){
			continue;
		}
		space = currentLine.find(" ");
		sAmount = currentLine.substr(space + 1); //second number (is a string at this point)
		//cout << sAmount << endl;
		//cout << "levelOne.txt Line:" << lineNumber << " type: " << sType << " amount: " << sAmount << endl;
		amount = stoi(sAmount); //string to int, exclusive to c++ 11
		if (sType == "0" || sType == "1" || sType == "2" || sType == "3" || sType == "4" || sType == "5" || sType == "6" || sType == "7" || sType == "8" || sType == "9" )
		{
			type = stoi(sType);
		}
		else{
			type = 1000;
		}
		//cout << "amount is " << amount << " and type is " << type << endl;
		//cout << "The current column is " << column << " and the current row is " << row << endl;
			for (int i = 0; i < amount; i++){
				sf::Sprite* tempSprite = new sf::Sprite();
				if (type == 1){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 16, 8, 8 *column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, false, false); //#1  this is a dot
					numDots++;
				}
				else if (type == 2){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 8, 24, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, false, false);
					levelMatrix[column][row]->makeBigDot();
					numDots++;
				}
				else if (type == 3){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 0, 0, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
				}
				else if (type == 4){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 8, 0, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
				}
				else if (type == 5){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 216, 0, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
				}
				else if (type == 6){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 0, 16, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
				}
				else if (type == 7){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 0, 72, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
				}
				else if (type == 8){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 216, 72, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
				}
				else if (type == 9){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 216, 8, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
				}
				else if (type == 0){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 0, 80, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, false, true);
				}
				else if (sType == "A"){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 8, 240, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
				}
				else{
					continue;
				}
				column++;
				if (column >= 28){
					column = 0;
					row++;
				}
				//cout << "The current column is " << column << " and the current row is " << row << endl;
			}
		}
	levelFile.close();
	this->dots = numDots;
	//trying to get memcpy to work so i can simply copy my array over when i restart.
	//copyMatrix = levelMatrix;
	//memcpy(copyMatrix, levelMatrix, sizeof(Tile*) * 28 * 36);
}

Tile*** Level::getLevelMatrix(){
	return levelMatrix;
}

void Level::setTile(int x, int y, Tile* tile){
	this->levelMatrix[x][y] = tile;
}

void Level::resetLevel(fstream& levelFile, sf::Texture* txt, int level){
	if (level == 1){
		levelFile.open("levelOne.txt");
	}
	if (level == 2){
		levelFile.open("levelTwo.txt");
	}
	levelFile.clear(); //clears the EOF flag
	levelFile.seekg(0, levelFile.ios::beg);
	string currentLine;
	string sType;
	string sAmount;
	int type = 0; //the type of wall
	int amount = 0; //the number of that wall
	int dLocation = 0;
	int lineNumber = 0;
	int space = 0;
	int row = 0;
	int column = 0;
	int numDots = 0;
	//levelMatrix = new Tile**[28];
	//for (int i = 0; i < 28; i++){
		//levelMatrix[i] = new Tile*[36];
	//}

	while (getline(levelFile, currentLine)){
		lineNumber++;
		sType = currentLine.substr(0, 1); //type of wall
		if (sType == "#"){
			continue;
		}
		space = currentLine.find(" ");
		sAmount = currentLine.substr(space + 1); //second number (is a string at this point)
		//cout << sAmount << endl;
		//cout << "levelOne.txt Line:" << lineNumber << " type: " << sType << " amount: " << sAmount << endl;
		amount = stoi(sAmount); //string to int, exclusive to c++ 11
		if (sType == "0" || sType == "1" || sType == "2" || sType == "3" || sType == "4" || sType == "5" || sType == "6" || sType == "7" || sType == "8" || sType == "9")
		{
			type = stoi(sType);
		}
		else{
			type = 1000;
		}
		//cout << "amount is " << amount << " and type is " << type << endl;
		//cout << "The current column is " << column << " and the current row is " << row << endl;
		for (int i = 0; i < amount; i++){
			sf::Sprite* tempSprite = new sf::Sprite();
			if (type == 1){
				levelMatrix[column][row] = new Tile(tempSprite, txt, 16, 8, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, false, false); //#1  this is a dot
				numDots++;
			}
			else if (type == 2){
				levelMatrix[column][row] = new Tile(tempSprite, txt, 8, 24, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, false, false);
				levelMatrix[column][row]->makeBigDot();
				numDots++;
			}
			else if (type == 3){
				levelMatrix[column][row] = new Tile(tempSprite, txt, 0, 0, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
			}
			else if (type == 4){
				levelMatrix[column][row] = new Tile(tempSprite, txt, 8, 0, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
			}
			else if (type == 5){
				levelMatrix[column][row] = new Tile(tempSprite, txt, 216, 0, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
			}
			else if (type == 6){
				levelMatrix[column][row] = new Tile(tempSprite, txt, 0, 16, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
			}
			else if (type == 7){
				levelMatrix[column][row] = new Tile(tempSprite, txt, 0, 72, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
			}
			else if (type == 8){
				levelMatrix[column][row] = new Tile(tempSprite, txt, 216, 72, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
			}
			else if (type == 9){
				levelMatrix[column][row] = new Tile(tempSprite, txt, 216, 8, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
			}
			else if (type == 0){
				levelMatrix[column][row] = new Tile(tempSprite, txt, 0, 80, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, false, true);
			}
			else if (sType == "A"){
				levelMatrix[column][row] = new Tile(tempSprite, txt, 8, 240, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true, true);
			}
			else{
				continue;
			}
			column++;
			if (column >= 28){
				column = 0;
				row++;
			}
			//cout << "The current column is " << column << " and the current row is " << row << endl;
		}
	}
	levelFile.close();
	this->dots = numDots;
	//trying to get memcpy to work so i can simply copy my array over when i restart.
	//copyMatrix = levelMatrix;
	//memcpy(copyMatrix, levelMatrix, sizeof(Tile*) * 28 * 36);
}

void Level::renderLevel(sf::RenderWindow* wnd){
	for (int i = 0; i < 28; i++){
		for (int j = 0; j < 36; j++){
			wnd->draw(*(this->levelMatrix[i][j]->getSprite()));
		}
	}
}