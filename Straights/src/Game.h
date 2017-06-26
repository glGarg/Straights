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
	void beginRound();
	void playCard(Card&);
	void discardCard(Card&);
	void printDeck() const;
	void rageQuit();
	bool isLastPlayerHandEmpty() const;
	void tallyScores();
	bool isOver() const;
private:
	bool isLegalMove(Card&) const;
	void displayGameState() const;
	void decideNextPlayer();
	void resetRound();
	const int PLAYER_COUNT;
	bool firstTurn_;
	bool isOver_;
	size_t nextPlayer_;
	size_t lastPlayer_;
	Deck deck_;
	Card::Rank curRank_;
	Card::Suit curSuit_;
	std::vector<Player *> players_;
	std::vector<int> playerScores_;
	std::map<Card::Suit, std::vector<Card>> cardsPlayed_;
};

