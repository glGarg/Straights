#pragma once
#include <string>
#include "Player.h"
#include "Command.h"
#include "Observer.h"

class View
{
public:
	View();
	virtual ~View();
	virtual void displayError(std::string) const = 0;
	virtual void printDeck(const std::vector<std::string>&) const = 0;
	void getUserInput();
	void attach(Observer *observer);
private:
	std::vector<Observer *> observers_;
};
