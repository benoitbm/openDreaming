#include "Graphics.hpp"

// #include <SFML/Audio.hpp>

int main(int argc, char** argv)
{
	/*
	sf::Music music;

	if (!music.openFromFile("mort.flac"))
	{
	}

	music.play();
	*/

	Graphics * window = new Graphics ();

	window->display();

	return 0;
}