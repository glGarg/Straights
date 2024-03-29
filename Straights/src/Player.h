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
	virtual const Card *makeNextMove(Card *&);
	bool play(const Card&);
	bool discard(const Card&);
	virtual bool isHuman() const = 0;
	bool isHandEmpty() const;
	int getScore() const;
	std::vector<std::string> getDiscardPileStr() const;
	std::vector<std::string> getHandStr() const;
	void reset();
protected:
	void removeCardFromHand(int);
	void addCardToDiscardPile(Card *card);
private:
	int getCardIndex(const Card&) const;
	std::vector<Card *> hand_;
	std::vector<Card *> discardPile_;
};
