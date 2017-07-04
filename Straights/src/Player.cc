#include "Player.h"
#include "Game.h"

Player::Player() {}

Player::Player(std::vector<Card *>& hand, std::vector<Card *>& discardPile) : hand_(hand), discardPile_(discardPile) {}

Player::Player(std::vector<Card *>&& hand, std::vector<Card *>&& discardPile) : hand_(std::move(hand)), discardPile_(std::move(discardPile)) {}

Player::~Player() {}

void Player::setHand(std::vector<Card *>& hand)
{
	hand_ = std::move(hand);
}

std::vector<Card *> Player::getHand()
{
	return hand_;
}

std::vector<Card*> Player::getDiscardPile()
{
	return discardPile_;
}

// for a computer player, determine and make the next move
const Card *Player::makeNextMove(Card *&discarded)
{
	// find a legal card to play for given suit and rank
	for (size_t i = 0; i < hand_.size(); ++i)
	{
		if (Game::isLegalMove(*hand_[i]))
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

// "play" function for a human player
bool Player::play(const Card& c)
{
	int index = getCardIndex(c);
	if (index != -1)
	{
		hand_.erase(hand_.begin() + index);
		return true;
	}
	return false;
}

// "discard" function for a human player
bool Player::discard(const Card& c)
{
	int index = getCardIndex(c);
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

// get a player's score based on the player's discard pile for the given round
int Player::getScore() const
{
	int score = 0;
	for (size_t i = 0; i < discardPile_.size(); ++i)
	{
		score += discardPile_[i]->rank() + 1;
	}

	return score;
}

std::vector<std::string> Player::getDiscardPileStr() const
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

int Player::getCardIndex(const Card& card) const
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
