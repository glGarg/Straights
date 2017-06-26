#pragma once
#include "View.h"

class TextView : public View
{
public:
	TextView(GameController *, Game *);
	virtual ~TextView();
	virtual void showMessage(std::string) const override;
	virtual void showError(std::string) const override;
	virtual void showPlayerPlay(int, std::string) const override;
	virtual void showPlayerDiscard(int, std::string) const override;
	void printDeck(const std::vector<std::string>&) const override;
	void showCardList(std::string, std::vector<std::string>&) const override;
	bool isPlayerHuman() const override;
};
