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

const Card *Player::makeNextMove(const Card::Suit& suit, const Card::Rank& rank, Card *&discarded)
{
	// find a legal card to play for given suit and rank
	for (size_t i = 0; i < hand_.size(); ++i)
	{
		if (hand_[i]->rank() == rank || (hand_[i]->suit() == suit &&
			((rank.rank() != 0 && hand_[i]->rank().rank() == (rank.rank() - 1)) ||
			(rank.rank() != 12 && hand_[i]->rank().rank() == (rank.rank() + 1)))))
		{
			Card *played = hand_[i];
			hand_.erase(hand_.begin() + i);
			return played;
		}
	}

	discardPile_.push_back(hand_[0]);
	hand_.erase(hand_.begin());
	discarded = discardPile_.back();
	return nullptr;
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

bool Player::isHandEmpty() const
{
	return hand_.size() == 0;
}

int Player::getScore() const
{
	int score = 0;
	for (size_t i = 0; i < discardPile_.size(); ++i)
	{
		score += discardPile_[i]->rank() + 1;
	}

	return score;
}

std::vector<std::string> Player::getDiscardPile() const
{
	std::vector<std::string> discardedCards;

	for (size_t i = 0; i < discardPile_.size(); ++i) 
	{
		discardedCards.push_back(*discardPile_[i]);
	}
	return discardedCards;
}

void Player::reset()
{
	discardPile_.erase(discardPile_.begin(), discardPile_.end());
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
