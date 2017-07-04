#pragma once
#include <memory>
#include <map>
#include "Card.h"

class Player
{
public:
	Player();
	Player(std::vector<Card *>&, std::vector<Card *>&);
	Player(std::vector<Card *>&&, std::vector<Card *>&&);
	virtual ~Player();
	void setHand(std::vector<Card *>&);
	std::vector<Card *> getHand();
	std::vector<Card *> getDiscardPile();
	const Card *makeNextMove(Card *&);
	bool play(const Card&);
	bool discard(const Card&);
	virtual bool isHuman() const = 0;
	bool isHandEmpty() const;
	int getScore() const;
	std::vector<std::string> getDiscardPileStr() const;
	void reset();
private:
	int getCardIndex(const Card&) const;
	std::vector<Card *> hand_;
	std::vector<Card *> discardPile_;
};
