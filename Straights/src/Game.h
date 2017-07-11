#pragma once
#include <iostream>
#include <string>
#include <map>
#include "Deck.h"
#include "Subject.h"
#include "HumanPlayer.h"
#include "SmartComputerPlayer.h"
#include "GuiView.h"

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
	void restartGame();
	bool isLastPlayerHandEmpty() const;
	void tallyScores();
	bool isOver() const;
	int getNextPlayerIndex() const;
	bool isPlayerIndexHuman(int) const;
	std::vector<std::string> getPlayerHandStr(int) const;
	std::vector<std::string> getPlayerLegalPlays(int) const;
	static bool isLegalMove(Card&);
	
	class GameException
	{
	public:
		GameException(const std::string = "");
		std::string what() const;
	private:
		const std::string message_;
	};

	class IllegalDiscardException : public GameException
	{
	public:
		IllegalDiscardException(Card&);
	};

	class GameOverException : public GameException {};
private:
	void displayGameState() const;
	void decideNextPlayer();
	void resetRound();
	static bool firstTurn_;
	
	static std::map<Card::Suit, std::vector<Card>> cardsPlayed_;
	static const int PLAYER_COUNT;
	static bool isOver_;
	static bool newGameStarted_;
	size_t nextPlayer_;
	size_t lastPlayer_;
	std::vector<Player *> players_;
	std::vector<int> playerScores_;
	Deck deck_;
};
