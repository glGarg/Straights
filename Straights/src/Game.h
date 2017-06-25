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
	bool isFirstPlayerHandEmpty() const;
	bool tallyScores();
private:
	void outputPlayMove(int, std::string) const;
	void outputDiscardMove(int, std::string) const;
	bool isLegalMove(Card&) const;
	void displayGameState() const;
	void decideNextPlayer();
	void resetRound();
	const int PLAYER_COUNT;
	bool firstTurn_;
	size_t nextPlayer_;
	size_t firstPlayer_;
	Deck deck_;
	Card::Rank curRank_;
	Card::Suit curSuit_;
	std::vector<Player *> players_;
	std::vector<int> playerScores_;
	std::map<Card::Suit, std::vector<Card>> cardsPlayed_;
};

