#pragma once
#include <string>
#include "Command.h"
#include "GameController.h"

class View
{
public:
	View(GameController *, Game *);
	virtual ~View();
	void init();
	virtual void showMessage(std::string) const = 0;
	virtual void showError(std::string) const = 0;
	virtual void showPlayerPlay(int, std::string) const = 0;
	virtual void showPlayerDiscard(int, std::string) const = 0;
	virtual void printDeck(const std::vector<std::string>&) const = 0;
	virtual bool isPlayerHuman() const = 0;
	virtual void showCardList(std::string, std::vector<std::string>&) const = 0;
	void getUserInput();
private:
	GameController *controller_;
	Game *game_;
};
