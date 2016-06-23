#include "Graphics.hpp"

#include <SFML/Audio.hpp>

int main(int argc, char** argv)
{
	Graphics * window = new Graphics ();

	window->display();

	return 0;
}