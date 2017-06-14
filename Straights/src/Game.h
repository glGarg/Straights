#pragma once
#include <iostream>
#include <string>
#include "Deck.h"
#include "Observer.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "TextView.h"

class Game : public Observer
{
public:
	Game();
	~Game();
	void run();
	bool notify(Command&) override;
private:
	bool isLegalMove(Card &) const;
	int PLAYER_COUNT;
	size_t nextPlayer_;
	Deck deck_;
	Card::Rank curRank_;
	Card::Suit curSuit_;
	std::vector<Player *> players_;
	View *view_;
};
