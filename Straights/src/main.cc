#include <iostream>
#include "Game.h"

int main(int argc, char **argv)
{
	Game game;
	if (argc > 1)
	{
		seed = static_cast<int>(*argv[1]);
	}

	game.run();
	return 0;
}