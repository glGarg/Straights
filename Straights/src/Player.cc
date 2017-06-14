#include "Player.h"

Player::Player() {}

Player::Player(std::vector<Card *>& hand) : hand_(hand) {}

Player::Player(std::vector<Card *>&& hand) : hand_(std::move(hand)) {}

Player::~Player() {}

void Player::setHand(std::vector<Card *>& hand)
{
	hand_ = std::move(hand);
}

std::vector<Card *> Player::getHand()
{
	return hand_;
}

void Player::makeNextMove(const Card::Suit& suit, const Card::Rank& rank)
{
	// find a legal card to play for given suit and rank

}

bool Player::play(const Card& c)
{
	int index = hasCard(c);
	if (index != -1)
	{
		hand_.erase(hand_.begin() + index);
		return true;
	}
	return false;
}

bool Player::discard(const Card& c)
{
	int index = hasCard(c);
	if (index != -1)
	{
		discardPile_.push_back(hand_[index]);
		hand_.erase(hand_.begin() + index);
		return true;
	}
	return false;
}

int Player::hasCard(const Card& card) const
{
	for (size_t i = 0; i < hand_.size(); ++i)
	{
		if(hand_[i]->rank() == card.rank() && hand_[i]->suit() == card.suit())
		{
			return i;
		}
	}
	return -1;
}