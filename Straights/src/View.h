#pragma once
#include <string>
#include "Command.h"
#include "Observer.h"
#include "GameController.h"

class View : public Observer
{
public:
	View(GameController *, Game *);
	virtual ~View();
	virtual void displayError(std::string) const = 0;
	virtual void printDeck(const std::vector<std::string>&) const = 0;
	virtual void update() const = 0;
	void getUserInput();
private:
	GameController *controller_;
	Game *game_;
};
