#include "level.h"

Level::Level(){
	Tile*** levelMatrix = new Tile**[28];
	for (int i = 0; i < 28; i++){
		levelMatrix[i] = new Tile*[36];
		//levelMatrix[1][1]->getSprite();
	}
}