#pragma once
#include <iostream>
#include <string>
#include <map>
#include "Deck.h"
#include "Subject.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "TextView.h"

class Game : public Subject
{
public:
	Game();
	~Game();
	void init();
	void playCard(Card&);
	void discardCard(Card&);
	void printDeck() const;
	void rageQuit();
	
private:
	bool isLegalMove(Card&) const;
	void displayGameState() const;
	void decideNextPlayer();
	const int PLAYER_COUNT;
	size_t nextPlayer_;
	Deck deck_;
	Card::Rank curRank_;
	Card::Suit curSuit_;
	std::vector<Player *> players_;
	std::map<Card::Suit, std::vector<Card>> cardsPlayed_;
};
