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
bool dead = false;
bool isMoving = false;
bool resetClock = false;
bool waitingForRestart = false;
void restartLevel(Player* pman, Ghost* red, Ghost* orange, Ghost* pink, Ghost* teal); //forward identifier
int lives = 3;
bool onLevelOne = false;
bool onLevelTwo = false;
bool mainMenu = true;
int main(int argc, char** argv)
{ //456 is the start of pacman stuff
	//sf::IntRect testRect(456, 0, 16, 16);

	fstream levelOneFile;
	fstream levelTwoFile;

	GLOBAL_SCALE = 3.f;
	sf::Int32 aniSpeed = 200;

	//::Clock godClock;
	sf::Clock gameClock;
	sf::Clock pacClock;
	sf::Clock aniClock;
	sf::Clock redClock;
	sf::Clock pinkClock;
	sf::Clock tealClock;
	sf::Clock orangeClock;

	

	sf::RenderWindow window(sf::VideoMode(672, 864), "Pacman!"); //classic pacman is 224 x 288  84 x 108 tiles

	sf::Font font;
	if (!font.loadFromFile("pacText.ttf")){
		return EXIT_FAILURE;
	}
	sf::Text text;
	text.setFont(font);
	text.setString("Press Space to start Pacman!");
	text.setCharacterSize(24);
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setPosition((672 / 2) - 100, 864 - 200);
	text.setColor(sf::Color::Black);

	sf::Texture* pTexture = new sf::Texture();
	if (!pTexture->loadFromFile("Pacman_spritesheet.png")){
		return EXIT_FAILURE;
	}
	
	sf::Sprite* lifeSpriteOne = new sf::Sprite();
	sf::Sprite* lifeSpriteTwo = new sf::Sprite();
	sf::Sprite* lifeSpriteThree = new sf::Sprite();
	sf::Sprite* pSprite = new sf::Sprite();
	sf::Sprite* gSprite = new sf::Sprite();
	sf::Sprite* pinkSprite = new sf::Sprite();
	sf::Sprite* tealSprite = new sf::Sprite();
	sf::Sprite* orangeSprite = new sf::Sprite();
	sf::Sprite* tSprite = new sf::Sprite();
	sf::Sprite* tSprite2 = new sf::Sprite();
	sf::Sprite* tSprite3 = new sf::Sprite();
	sf::Sprite* tSprite4 = new sf::Sprite();
	pSprite->setTexture(*pTexture, true);
	//sprites for lives.
	lifeSpriteOne->setTexture(*pTexture, true);
	lifeSpriteTwo->setTexture(*pTexture, true);
	lifeSpriteThree->setTexture(*pTexture, true);
	sf::IntRect* tBox = new sf::IntRect(472, 0, 16, 16); //left, top , width, height, 456 is start of spritesheet
	lifeSpriteOne->setTextureRect(*tBox);
	lifeSpriteTwo->setTextureRect(*tBox);
	lifeSpriteThree->setTextureRect(*tBox);
	lifeSpriteOne->setPosition(100, 750);
	lifeSpriteTwo->setPosition(132, 750);
	lifeSpriteThree->setPosition(164, 750);


	Level* levelOne = new Level(levelOneFile, pTexture, 1);
	Level* levelTwo = new Level(levelTwoFile, pTexture, 2);


	Player* pacman = new Player(pSprite, pTexture, levelOne);
	Ghost pink(pinkSprite, pTexture, levelOne, "Pink");
	Ghost red(gSprite, pTexture, levelOne, "Red");
	Ghost teal(tealSprite, pTexture, levelOne, "Teal");
	Ghost orange(orangeSprite, pTexture, levelOne, "Orange");
	
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("score " + to_string(pacman->score));
	scoreText.setCharacterSize(24);
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	scoreText.setPosition((672 / 2), 864 - 120);
	scoreText.setColor(sf::Color::White);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed){
				if (!mainMenu){

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
				else{
					if (event.key.code == sf::Keyboard::Space){
						mainMenu = false;
						onLevelOne = true;
						red.setLevel(levelOne);
						orange.setLevel(levelOne);
						pink.setLevel(levelOne);
						teal.setLevel(levelOne);
					}
				}
			}
		}
		if (!mainMenu){
			if (pacman->dotsLeft == 0){
				onLevelOne = false;
				onLevelTwo = true;                                     //REPLACE LEVEL TRANSITION
			}
			if ((red.hasKilledPacman(pacman) || orange.hasKilledPacman(pacman) || pink.hasKilledPacman(pacman) || teal.hasKilledPacman(pacman)) /*&& !waitingForRestart*/){
				//cout << "NO PACMAN D:" << endl;
				cout << "im here" << endl;
				dead = true;
			}
			//cout << dead << endl;
			if (!dead){ //as long as pacman is still alive D:
				red.moveGhost(&redClock, pacman, levelOne, &red);
				teal.moveGhost(&tealClock, pacman, levelOne, &red);
				pink.moveGhost(&pinkClock, pacman, levelOne, &red);
				orange.moveGhost(&orangeClock, pacman, levelOne, &red);
				pacman->checkPosition(&window);
				if (isMoving == true){
					pacman->movePlayer(&pacClock, pacman->getDirection());

					if (aniClock.getElapsedTime().asMilliseconds() >= aniSpeed){
						red.playAnimation(pacman, pacman->godClock);
						teal.playAnimation(pacman, pacman->godClock);
						orange.playAnimation(pacman, pacman->godClock);
						pink.playAnimation(pacman, pacman->godClock);
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
				if (waitingForRestart == false){
					pacman->restartClock->restart();
					waitingForRestart = true;
				}
				if (waitingForRestart && pacman->restartClock->getElapsedTime().asSeconds() > 4.f){
					restartLevel(pacman, &red, &orange, &pink, &teal);
					dead = false;
					red.resetGhost();
					orange.resetGhost();
					pink.resetGhost();
					teal.resetGhost();
					//pacman->movePlayer(&pacClock, pacman->getDirection());
					pacman->restartPacman();
					if (lives == 0){
						//window.close(); //REPLACE THIS WITH GOING TO MAIN MENU
						mainMenu = true;
						levelOne->resetLevel(levelOneFile, pTexture, 1);
						levelTwo->resetLevel(levelTwoFile, pTexture, 2);
						lives = 3;
					}
					waitingForRestart = false;                                                  //RESTART THE GAME HERE
					gameClock.restart();
				}

			}
			//if pacman is not invincible proceed with normal ghost AI
			if (pacman->checkGodStatus() == false){
				if (gameClock.getElapsedTime().asSeconds() > 20){
					gameClock.restart();
					red.toggleScatter();
					pink.toggleScatter();
					orange.toggleScatter();
					teal.toggleScatter();
					//cout << "its been 20 seconds, game clock restarted!" << endl;

				}
			}
			else{ //otherwise, make the ghosts scared
				if (resetClock == false){//restart the godclock because its always running (but only once per pickup)
					//cout << "godmode is on!" << endl;
					pacman->godClock->restart();
					resetClock = true;
					red.togglePanic();
					teal.togglePanic();
					pink.togglePanic();
					orange.togglePanic();
				}
				else{
					if (pacman->godClock->getElapsedTime().asSeconds() > 8){
						//cout << "Oh no, god mode is off!" << endl;
						pacman->toggleGod();
						resetClock = false;
						cout << pacman->checkGodStatus() << endl;
						red.togglePanic();
						teal.togglePanic();
						pink.togglePanic();
						orange.togglePanic();
					}
				}
			}


			window.clear(sf::Color::Black);
			if (onLevelOne == true){
				levelOne->renderLevel(&window);
			}
			else if (onLevelTwo == true){
				levelTwo->renderLevel(&window);
			}
			if (lives == 3){
				window.draw(*(lifeSpriteOne));
				window.draw(*(lifeSpriteTwo));
				window.draw(*(lifeSpriteThree));
			}
			else if (lives == 2){
				window.draw(*(lifeSpriteOne));
				window.draw(*(lifeSpriteTwo));
			}
			else if (lives == 1){
				window.draw(*(lifeSpriteOne));
			}
			scoreText.setString("score " + to_string(pacman->score));
			window.draw(scoreText);
			window.draw(*(red.getSprite()));
			window.draw(*(teal.getSprite()));
			window.draw(*(pink.getSprite()));
			window.draw(*(orange.getSprite()));
			window.draw(*(pacman->getSprite()));

			window.display();
		}
		else{
			window.clear(sf::Color::White);
			window.draw(text);
			window.display();
		}
	}

	return 0;
}
/*bool isDead = false;
	bool isScatter = false;
	bool isScared = false;
	bool inPrison = true;
	bool gameStart = true;*/
void restartLevel(Player* pman, Ghost* red, Ghost* orange, Ghost* pink, Ghost* teal){
	dead = false;
	lives--;
}
//test update