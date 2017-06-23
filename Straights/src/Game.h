#pragma once
#include <iostream>
#include <string>
#include "Deck.h"
#include "Subject.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "TextView.h"

class Game : Subject
{
public:
	Game();
	~Game();
	void playCard(Card&);
	void discardCard(Card&);
	void printDeck() const;
	void rageQuit();
	void decideNextPlayer();
private:
	void init();
	bool isLegalMove(Card&) const;
	const int PLAYER_COUNT;
	size_t nextPlayer_;
	Deck deck_;
	Card::Rank curRank_;
	Card::Suit curSuit_;
	std::vector<Player *> players_;
};
