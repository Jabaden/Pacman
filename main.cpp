//sfml-graphics-s.lib;sfml-window-s.lib;sfml-system-s.lib;opengl32.lib;freetype.lib;jpeg.lib;winmm.lib;gdi32.lib;sfml-main.lib;sfml-audio-s.lib;openal32.lib;flac.lib;vorbisenc.lib;vorbisfile.lib;vorbis.lib;ogg.lib;

//D:\Program Files (x86)\SFML\SFML-2.3.1\include    

//D:\Program Files(x86)\SFML\SFML - 2.3.1\lib

//SFML_STATIC

#include <SFML/Graphics.hpp>
#include <iostream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "Player.h"
#include "Tile.h"
#include "Game.h"
#include "Ghost.h"
#include "Level.h"
using namespace std;

#define UP 0
#define DOWN 180
#define LEFT 270
#define RIGHT 90

float GLOBAL_SCALE;

int main(int argc, char** argv)
{ //456 is the start of pacman stuff
	//sf::IntRect testRect(456, 0, 16, 16);

	fstream levelOneFile;

	GLOBAL_SCALE = 3.f;

	bool isMoving = false;
	bool dead = false;
	sf::Int32 aniSpeed = 200;

	sf::Clock pacClock;
	sf::Clock aniClock;
	sf::Clock redClock;

	sf::RenderWindow window(sf::VideoMode(672, 864), "Pacman!"); //classic pacman is 224 x 288  84 x 108 tiles

	sf::Texture* pTexture = new sf::Texture();
	if (!pTexture->loadFromFile("Pacman_spritesheet.png")){
		return EXIT_FAILURE;
	}

	sf::Sprite* pSprite = new sf::Sprite();
	sf::Sprite* gSprite = new sf::Sprite();
	sf::Sprite* tSprite = new sf::Sprite();
	sf::Sprite* tSprite2 = new sf::Sprite();
	sf::Sprite* tSprite3 = new sf::Sprite();
	sf::Sprite* tSprite4 = new sf::Sprite();

	pSprite->setTexture(*pTexture, true);

	Tile* testTile = new Tile(tSprite, pTexture, 216, 72, 8 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); // #7
	
	cout << "testTile's wall status is" << testTile->getWallStatus() << endl;
	
	Tile* testTile2 = new Tile(tSprite2, pTexture, 16, 8, 200, 0, false); //#1  this is a dot
	Tile* testTile3 = new Tile(tSprite3, pTexture, 8, 240, 16, 500, true);//ghost
	Tile* testTile4 = new Tile(tSprite4, pTexture, 8, 0, 16 * GLOBAL_SCALE, 8 * GLOBAL_SCALE, true); //#4

	Tile** arrayOfTiles[3];

	Level* levelOne = new Level(levelOneFile, pTexture);

	Tile*** tempTriple = levelOne->getLevelMatrix();

	Player* pacman = new Player(pSprite, pTexture, levelOne);
	Ghost red(gSprite, pTexture, levelOne);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed){
				if (isMoving == false){
					pacClock.restart();
				}
				if (event.key.code == sf::Keyboard::W){
					pacman->setDirection(UP);
					isMoving = true;
				}
				else if (event.key.code == sf::Keyboard::A){
					pacman->setDirection(LEFT);
					isMoving = true;
				}
				else if (event.key.code == sf::Keyboard::S){
					pacman->setDirection(DOWN);
					isMoving = true;
				}
				else if (event.key.code == sf::Keyboard::D){
					//cout << "i pressed right (D)" << endl;
					pacman->setDirection(RIGHT);
					isMoving = true;
				}
				
				if (event.key.code == sf::Keyboard::Escape){
					isMoving = false;
					dead = true;
				}
			}
		}
		if (!dead){
			if (isMoving == true){
				pacman->movePlayer(&pacClock, pacman->getDirection());

				if (aniClock.getElapsedTime().asMilliseconds() >= aniSpeed){
					pacman->playRun();
					aniClock.restart();
				}
			}
		}
		else{
			if (aniClock.getElapsedTime().asMilliseconds() >= aniSpeed){
				pacman->playDeath();
				aniClock.restart();
			}
		}
		red.moveGhost(&redClock, pacman, levelOne);
		pacman->checkPosition(&window);
		window.clear(sf::Color::Black);
		levelOne->renderLevel(&window);
		window.draw(*(red.getSprite()));
		window.draw(*(pacman->getSprite()));
		
		window.display();
	}
	return 0;
}
//test update