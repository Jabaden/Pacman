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

Level::Level(fstream& levelFile, sf::Texture* txt){
	levelFile.open("levelOne.txt");
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
		//cout << "amount is " << amount << " and type is " << type << endl;
		//cout << "The current column is " << column << " and the current row is " << row << endl;
			for (int i = 0; i < amount; i++){
				sf::Sprite* tempSprite = new sf::Sprite();
				if (type == 1){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 16, 8, 8 *column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, false); //#1  this is a dot
				}
				else if (type == 2){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 8, 24, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, false);
				}
				else if (type == 3){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 0, 0, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true);
				}
				else if (type == 4){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 8, 0, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true);
				}
				else if (type == 5){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 216, 0, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true);
				}
				else if (type == 6){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 0, 16, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true);
				}

				else if (type == 7){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 0, 72, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true);
				}
				else if (type == 8){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 216, 72, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true);
				}
				else if (type == 9){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 216, 8, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true);
				}
				else if (type == 0){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 0, 80, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true);
				}
				else if (sType == "B"){
					levelMatrix[column][row] = new Tile(tempSprite, txt, 0, 80, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, false);
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
		/*
		else{
			//IF ITS ONLY ONE HERE
			sf::Sprite* tempSprite = new sf::Sprite();
			if (type == 1){
				levelMatrix[column][row] = new Tile(tempSprite, txt, 16, 8, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, false); //#1  this is a dot
			}
			else if (type == 2){
				levelMatrix[column][row] = new Tile(tempSprite, txt, 8, 24, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, false);
			}
			else if (type == 3){
				//Tile* testTile = new Tile(tSprite, pTexture, 0, 0, 8 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); // #3
				levelMatrix[column][row] = new Tile(tempSprite, txt, 0, 0, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true);
			}
			else if (type == 4){
				//Tile* testTile4 = new Tile(tSprite4, pTexture, 8, 0, 16 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); //#4
				levelMatrix[column][row] = new Tile(tempSprite, txt, 8, 0, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true);
			}
			else if (type == 5){
				//Tile* testTile = new Tile(tSprite, pTexture, 216, 0, 8 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); // #5
				levelMatrix[column][row] = new Tile(tempSprite, txt, 216, 0, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true);
			}
			else if (type == 6){
				//Tile* testTile = new Tile(tSprite, pTexture, 0, 16, 8 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); // #6
				levelMatrix[column][row] = new Tile(tempSprite, txt, 216, 0, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true);
			}

			else if (type == 7){
				//Tile* testTile = new Tile(tSprite, pTexture, 0, 72, 8 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); // #7
				levelMatrix[column][row] = new Tile(tempSprite, txt, 0, 72, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true);
			}
			else if (type == 8){
				//Tile* testTile = new Tile(tSprite, pTexture, 216, 72, 8 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); // #8
				levelMatrix[column][row] = new Tile(tempSprite, txt, 216, 72, 8 * column * GLOBAL_SCALE, 8 * row * GLOBAL_SCALE, true);
			}
			else{
				continue;
			}
			column++;
			if (column > 28){
				column = 0;
				row++;
			}
		}
		*/
		
	
	//for (int i = 0; i < 28; i++){
		//for (int j = 0; j < 36; j++){
			//sf::Sprite* tempSprite = new sf::Sprite();
			//levelMatrix[i][j] = new Tile(i * (8 * GLOBAL_SCALE), j * (8 * GLOBAL_SCALE));
		//}
	//}
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