#pragma once
#include "Deck.h"
#include "Command.h"
#include "Player.h"
#include <iostream>
#include <string>

using std::cin;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Deck deck_;
	std::vector<Player *> players_;
};
