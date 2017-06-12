#pragma once
#include <random>
#include "Card.h"

extern int seed;

class Deck
{
public:
	Deck();
	~Deck();
	void shuffle();
private:
	int CARD_COUNT;
	std::vector<Card *> cards_;
};

