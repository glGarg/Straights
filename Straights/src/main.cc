#include <iostream>
#include "Game.h"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		seed = std::stoi(argv[1]);
	}

	Game game;
	GameController controller(&game);
	TextView view(&controller, &game);
	view.init();

	return 0;
}