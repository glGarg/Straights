#include <iostream>
#include "Game.h"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		seed = static_cast<int>(*argv[1]);
	}
	
	Game game;
	GameController controller(&game);
	TextView view(&controller, &game);
	view.init();

	return 0;
}