#pragma once
#include <iostream>
#include <string>
#include "Deck.h"
#include "Command.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

using std::cin;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	bool isLegalMove(Card &) const;
	int PLAYER_COUNT;
	Deck deck_;
	Card::Rank curRank_;
	Card::Suit curSuit_;
	std::vector<Player *> players_;
};
