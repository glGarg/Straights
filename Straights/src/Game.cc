#include "Game.h"

Game::Game() : players_(4) {}

Game::~Game() {}

void Game::run()
{
	deck_.shuffle();
	while (true)
	{
		Command c;
		cin >> c;
		if (cin.fail())
		{
			break;
		}

		switch (c.type)
		{
		case Command::Type::PLAY:
			break;
		case Command::Type::DISCARD:
			break;
		case Command::Type::DECK:
			break;
		case Command::Type::RAGEQUIT:
			break;
		case Command::Type::QUIT:
			return;
		default:
			break;
		}
	}
}