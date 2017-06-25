#pragma once
#include <memory>
#include "Card.h"

class Player
{
public:
	Player();
	Player(std::vector<Card *>&);
	Player(std::vector<Card *>&&);
	virtual ~Player();
	void setHand(std::vector<Card *>&);
	std::vector<Card *> getHand();
	const Card *makeNextMove(const Card::Suit&, const Card::Rank&, Card **);
	bool play(const Card&);
	bool discard(const Card&);
	virtual bool isHuman() const = 0;
	bool isHandEmpty() const;
	int getScore() const;
private:
	int hasCard(const Card&) const;
	std::vector<Card *> hand_;
	std::vector<Card *> discardPile_;
};
