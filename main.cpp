//sfml-graphics-s.lib;sfml-window-s.lib;sfml-system-s.lib;opengl32.lib;freetype.lib;jpeg.lib;winmm.lib;gdi32.lib;sfml-main.lib;sfml-audio-s.lib;openal32.lib;flac.lib;vorbisenc.lib;vorbisfile.lib;vorbis.lib;ogg.lib;

//D:\Program Files (x86)\SFML\SFML-2.3.1\include    

//D:\Program Files(x86)\SFML\SFML - 2.3.1\lib

//SFML_STATIC


#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "Pacman!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}