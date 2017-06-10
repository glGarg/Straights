#pragma once
#include <random>
#include "Card.h"

extern int seed;

class Straights
{
public:
	static Straights& Instance();
	void run();

private:
	Straights();
	virtual ~Straights();
	void shuffle();
	int CARD_COUNT;
	std::vector<Card *> cards_;
};

