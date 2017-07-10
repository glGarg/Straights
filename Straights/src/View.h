#pragma once
#include <string>
#include "Command.h"
#include "GameController.h"

class View
{
public:
	View();
	virtual ~View();
	virtual void init() = 0;
	virtual void reset();
	virtual void showMessage(std::string) const = 0;
	virtual void showError(std::string) const = 0;
	virtual void showPlayerPlay(int, std::string) = 0;
	virtual void showPlayerDiscard(int, std::string) = 0;
	virtual void printDeck(const std::vector<std::string>&) const = 0;
	virtual bool isPlayerHuman() const = 0;
	virtual void showCardList(std::string, std::vector<std::string>&) const = 0;
	virtual void showWinners(std::vector<int>&) const = 0;
	virtual void getUserInput() = 0;
	virtual void updateDisplay();
};
