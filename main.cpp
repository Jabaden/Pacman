//sfml-graphics-s.lib;sfml-window-s.lib;sfml-system-s.lib;opengl32.lib;freetype.lib;jpeg.lib;winmm.lib;gdi32.lib;sfml-main.lib;sfml-audio-s.lib;openal32.lib;flac.lib;vorbisenc.lib;vorbisfile.lib;vorbis.lib;ogg.lib;

//D:\Program Files (x86)\SFML\SFML-2.3.1\include    

//D:\Program Files(x86)\SFML\SFML - 2.3.1\lib

//SFML_STATIC

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

using namespace std;

#define UP 0
#define DOWN 180
#define LEFT 270
#define RIGHT 90

int main()
{ //456 is the start of pacman stuff
	//sf::IntRect testRect(456, 0, 16, 16);
	bool isMoving = false;

	sf::Clock pacClock;
	sf::RenderWindow window(sf::VideoMode(1900, 1080), "Pacman!");
	sf::Texture* pTexture = new sf::Texture();
	if (!pTexture->loadFromFile("Pacman_spritesheet.png")){
		return EXIT_FAILURE;
	}
	sf::Sprite* pSprite = new sf::Sprite();
	pSprite->setTexture(*pTexture, true);
	//pSprite->setTextureRect(testRect);
	//pSprite->setScale(3.f, 3.f);
	
	Player pacman(pSprite, pTexture);



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
				isMoving = true;
			}
		}
		if (isMoving == true){
			
			pacman.movePlayer(&pacClock, pacman.getDirection());
			pacman.playRun();
		}
		window.clear();
		window.draw(*(pacman.getSprite()));
		window.display();
	}

	return 0;
}
//test update