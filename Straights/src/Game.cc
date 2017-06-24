#include "Game.h"

Game::Game() : Subject(), PLAYER_COUNT(4), players_(PLAYER_COUNT), curRank_(Card::Rank::SEVEN),
			   curSuit_(Card::Suit::SPADE), nextPlayer_(0) {}

void Game::init()
{
	for (int i = 0; i < PLAYER_COUNT; ++i)
	{
		if (isPlayerHuman())
		{
			players_[i] = new HumanPlayer();
		}
		else
		{
			players_[i] = new ComputerPlayer();
		}
	}

	deck_.shuffle();
	int playerWith7OfSpades = -1;
	for (int i = 0; i < PLAYER_COUNT; ++i)
	{
		std::vector<Card *> hand = deck_.deal();
		if (playerWith7OfSpades == -1)
		{
			for (size_t j = 0; j < hand.size(); ++j)
			{
				if (hand[j]->rank().rank() == Card::Rank::SEVEN && hand[j]->suit().suit() == Card::Suit::SPADE)
				{
					playerWith7OfSpades = i;
				}
			}
		}
		players_[i]->setHand(hand);
	}
	std::swap(players_[playerWith7OfSpades], players_[0]);
}

Game::~Game()
{
	for (size_t i = 0; i < players_.size(); ++i)
	{
		if (players_[i] != nullptr)
		{
			delete players_[i];
		}
	}
}

void Game::playCard(Card& card)
{
	Player *p = players_[nextPlayer_];
	if (isLegalMove(card) && p->play(card))
	{
		curRank_ = card.rank();
		curSuit_ = card.suit();
		decideNextPlayer();
	}
	else
	{
		// tell view output error message
	}
}

void Game::discardCard(Card& card)
{
	Player *p = players_[nextPlayer_];
	if (p->discard(card) == true)
	{
		decideNextPlayer();
	}
	else
	{
		// view tells player must play legal card instead of discarding
	}
}

void Game::printDeck() const
{
	std::vector<std::string> cards(std::move(deck_.getCards()));
	//view_->printDeck(cards);
}

void Game::rageQuit()
{
	Player *p = players_[nextPlayer_];
	Player *temp = p;
	p = new ComputerPlayer(std::move(p->getHand()));
	delete temp;
	p->makeNextMove(curSuit_, curRank_);
	decideNextPlayer();
}

void Game::decideNextPlayer()
{
	bool wrapped = false;
	for (size_t i = nextPlayer_; i != nextPlayer_ || !wrapped; ++i)
	{
		if (i == players_.size())
		{
			i = 0;
			wrapped = true;
		}

		if (players_[i]->isHuman() == false)
		{
			const Card *cardPlayed = players_[i]->makeNextMove(curSuit_, curRank_);
			if (nullptr != cardPlayed)
			{
				curRank_ = Card::Rank(cardPlayed->rank().rank());
				curSuit_ = Card::Suit(cardPlayed->suit().suit());
			}
		}
		else
		{
			nextPlayer_ = i;
			break;
		}
	}
}

bool Game::isLegalMove(Card &c) const
{
	if (c.rank() == curRank_ || (c.suit() == curSuit_ && 
								((curRank_.rank() != 0 && c.rank() == Card::Rank(curRank_.rank() - 1)) ||
								(curRank_.rank() != 12 && c.rank() == Card::Rank(curRank_.rank() + 1)))))
	{
		return true;
	}
	return false;
}
