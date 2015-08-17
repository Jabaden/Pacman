#include "level.h"
#include "GameConfig.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
//DONT FORGET THAT YOU NEED TO POSITION THEM CORRECTLY. LOOK AT GLOBAL_SCALE * SOMETHING, THAT SOMETHING NEEDS TO CHANGE DEPENDING 
//ON ITS X,Y COORDINATE IN THE 2D ARRAY

//Tile* testTile2 = new Tile(tSprite2, pTexture, 16, 8, 200, 0, false); //#1  this is a dot
//Tile* testTile = new Tile(tSprite, pTexture, 8, 24, 8 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); #2
//Tile* testTile = new Tile(tSprite, pTexture, 0, 0, 8 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); // #3
//Tile* testTile4 = new Tile(tSprite4, pTexture, 8, 0, 16 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); //#4
//Tile* testTile = new Tile(tSprite, pTexture, 216, 0, 8 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); // #5
//Tile* testTile = new Tile(tSprite, pTexture, 0, 16, 8 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); // #6
//Tile* testTile = new Tile(tSprite, pTexture, 0, 72, 8 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); // #7
//Tile* testTile = new Tile(tSprite, pTexture, 216, 72, 8 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); // #8
//Tile* testTile = new Tile(tSprite, pTexture, 0, 80, 8 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); // NOTHING


using namespace std;

Level::Level(fstream& levelFile){
	levelFile.open("levelOne.txt");
	string currentLine;
	string sType;
	string sAmount;
	int type; //the type of wall
	int amount; //the number of that wall
	int dLocation;
	int lineNumber = 0;
	int space;
	while (getline(levelFile, currentLine)){
		lineNumber++;
		sType = currentLine.substr(0, 1); //type of wall
		if (sType == "#"){
			continue;
		}
		space = currentLine.find(" ");
		sAmount = currentLine.substr(space + 1); //second number (is a string at this point)
		cout << sAmount << endl;
		cout << "levelOne.txt Line:" << lineNumber << " type: " << sType << " amount: " << sAmount << endl;
		amount = stoi(sAmount); //string to int, exclusive to c++ 11
	}
	levelMatrix = new Tile**[28];
	for (int i = 0; i < 28; i++){
		levelMatrix[i] = new Tile*[36];
	}
	for (int i = 0; i < 28; i++){
		for (int j = 0; j < 36; j++){
			//sf::Sprite* tempSprite = new sf::Sprite();
			levelMatrix[i][j] = new Tile(i * (8 * GLOBAL_SCALE), j * (8 * GLOBAL_SCALE));
		}
	}
	levelFile.close();
}

Tile*** Level::getLevelMatrix(){
	return levelMatrix;
}

void Level::setTile(int x, int y, Tile* tile){
	this->levelMatrix[x][y] = tile;
}

void Level::renderLevel(sf::RenderWindow* wnd){
	for (int i = 0; i < 28; i++){
		for (int j = 0; j < 36; j++){
			wnd->draw(*(this->levelMatrix[i][j]->getSprite()));
		}
	}
}