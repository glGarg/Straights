#pragma once
#include "View.h"

class TextView : public View
{
public:
	TextView(GameController *, Game *);
	virtual ~TextView();
	void displayMessage(std::string) const override;
	void printDeck(const std::vector<std::string>&) const override;
	bool isPlayerHuman() const override;
};
