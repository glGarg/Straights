#pragma once
#include <random>
#include <memory>
#include "Card.h"

extern int seed;

class Deck
{
public:
	Deck();
	~Deck();
	void shuffle();
	std::vector<std::string> getCards() const;
	std::vector<Card *> deal();
private:
	int CARD_COUNT;
	int dealt_;
	std::vector<Card *> cards_;
};

