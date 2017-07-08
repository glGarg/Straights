#pragma once
#include "View.h"

class TextView : public View
{
public:
	TextView(GameController *, Game *);
	~TextView();
	void init() override;
	void showMessage(std::string) const override;
	void showError(std::string) const override;
	void showPlayerPlay(int, std::string) override;
	void showPlayerDiscard(int, std::string) override;
	void printDeck(const std::vector<std::string>&) const override;
	void showCardList(std::string, std::vector<std::string>&) const override;
	bool isPlayerHuman() const override;
	void getUserInput() override;
private:
	GameController *controller_;
	Game *game_;
};
