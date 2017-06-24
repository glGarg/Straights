#include "Deck.h"

int seed;

Deck::Deck() : CARD_COUNT(52), cards_(CARD_COUNT), dealt_(0)
{
	for (int i = 0; i < Card::Suit::MAX_SUIT; ++i)
	{
		for (int j = 0; j < Card::Rank::MAX_RANK; ++j)
		{
			cards_[i*13 + j] = new Card(Card::Rank(j), Card::Suit(i));
		}
	}
}

Deck::~Deck()
{
	for (size_t i = 0; i < cards_.size(); ++i)
	{
		if (nullptr != cards_[i])
		{
			delete cards_[i];
		}
	}
}

std::vector<Card *> Deck::deal()
{
	dealt_ = dealt_ % 52 + 13;
	return std::vector<Card *>(cards_.begin() + dealt_ - 13, cards_.begin() + dealt_);
}

std::vector<std::string> Deck::getCards() const
{
	std::vector<std::string> ret;
	std::string suits;
	for (auto &c : cards_)
	{
		ret.emplace_back(*c);
	}
	return ret;
}

void Deck::shuffle()
{
	static std::mt19937 rng(seed);
	int n = CARD_COUNT;
	while (n > 1) {
		int k = (int)(rng() % n);
		--n;
		Card *temp = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = temp;
	}
}
