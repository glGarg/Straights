#include "Straights.h"

int seed;

Straights::Straights() : CARD_COUNT(52), cards_(CARD_COUNT)
{
	for (int i = 0; i < Card::Suit::MAX_SUIT; ++i)
	{
		for (int j = 0; j < Card::Rank::MAX_RANK; ++j)
		{
			cards_[i*13 + j] = new Card(Card::Rank(j), Card::Suit(i));
		}
	}
}

Straights::~Straights()
{
	for (int i = 0; i < cards_.size(); ++i)
	{
		if (nullptr != cards_[i])
		{
			delete cards_[i];
		}
	}
}

Straights& Straights::Instance()
{
	static Straights s;
	return s;
}

void Straights::run()
{
	shuffle();
}

void Straights::shuffle()
{
	static std::mt19937 rng(seed);

	int n = CARD_COUNT;

	while (n > 1) {
		int k = (int)(rng() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}