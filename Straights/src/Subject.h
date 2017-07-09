#pragma once
#include <iostream>
#include <vector>
#include "View.h"

class Subject
{
public:
	Subject();
	virtual ~Subject();
	void subscribe(View *);
	void unsubscribe(View *);
protected:
	void showMessage(std::string) const;
	void showError(std::string) const;
	void showPlayerPlay(int, std::string) const;
	void showPlayerDiscard(int, std::string) const;
	void printCards(std::vector<std::string>&) const;
	bool isPlayerHuman(int) const;
	void showCardList(std::string, std::vector<std::string>&) const;
	void updateDisplay() const;
	void resetDisplay();
private:
	std::vector<View *> observers_;
};

