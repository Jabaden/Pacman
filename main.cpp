//sfml-graphics-s.lib;sfml-window-s.lib;sfml-system-s.lib;opengl32.lib;freetype.lib;jpeg.lib;winmm.lib;gdi32.lib;sfml-main.lib;sfml-audio-s.lib;openal32.lib;flac.lib;vorbisenc.lib;vorbisfile.lib;vorbis.lib;ogg.lib;

//D:\Program Files (x86)\SFML\SFML-2.3.1\include    

//D:\Program Files(x86)\SFML\SFML - 2.3.1\lib

//SFML_STATIC

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Tile.h"

using namespace std;

#define UP 0
#define DOWN 180
#define LEFT 270
#define RIGHT 90

int main()
{ //456 is the start of pacman stuff
	//sf::IntRect testRect(456, 0, 16, 16);
	bool isMoving = false;
	bool dead = false;
	sf::Int32 aniSpeed = 200;

	sf::Clock pacClock;
	sf::Clock aniClock;

	sf::RenderWindow window(sf::VideoMode(672, 864), "Pacman!"); //1900 x 1080 was what it was before classic pacman is 224 x 288

	sf::Texture* pTexture = new sf::Texture();
	if (!pTexture->loadFromFile("Pacman_spritesheet.png")){
		return EXIT_FAILURE;
	}

	sf::Sprite* pSprite = new sf::Sprite();
	sf::Sprite* tSprite = new sf::Sprite();
	sf::Sprite* tSprite2 = new sf::Sprite();
	sf::Sprite* tSprite3 = new sf::Sprite();

	pSprite->setTexture(*pTexture, true);
	tSprite->setTexture(*pTexture, true);
	tSprite2->setTexture(*pTexture, true);
	tSprite3->setTexture(*pTexture, true);

	
	Player pacman(pSprite, pTexture);
	Tile testTile(tSprite, pTexture);
	Tile testTile2(tSprite2, pTexture, 16, 0, 32, 0);
	Tile testTile3(tSprite3, pTexture, 8, 240, 16, 40);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::W){
					pacman.setDirection(UP);
				}
				if (event.key.code == sf::Keyboard::A){
					pacman.setDirection(LEFT);
				}
				if (event.key.code == sf::Keyboard::S){
					pacman.setDirection(DOWN);
				}
				if (event.key.code == sf::Keyboard::D){
					
					pacman.setDirection(RIGHT);
				}
				if (isMoving == false){
					pacClock.restart();
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
				pacman.movePlayer(&pacClock, pacman.getDirection());

				if (aniClock.getElapsedTime().asMilliseconds() >= aniSpeed){
					pacman.playRun();
					aniClock.restart();
				}
			}
		}
		else{
			if (aniClock.getElapsedTime().asMilliseconds() >= aniSpeed){
				pacman.playDeath();
				aniClock.restart();
			}
		}
		window.clear(sf::Color::White);
		window.draw(*(testTile.getSprite()));
		window.draw(*(testTile2.getSprite()));
		window.draw(*(testTile3.getSprite()));
		window.draw(*(pacman.getSprite()));
		
		window.display();
	}

	return 0;
}
//test update