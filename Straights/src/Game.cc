#include "Game.h"

Game::Game() : PLAYER_COUNT(4), players_(PLAYER_COUNT), curRank_(Card::Rank::SEVEN),
			   curSuit_(Card::Suit::SPADE), view_(new TextView()), nextPlayer_(0)
{
	for (int i = 0; i < PLAYER_COUNT; ++i)
	{
		players_[i] = new HumanPlayer();
	}

	view_->attach(this);
}

Game::~Game() {}

void Game::run()
{
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
	view_->getUserInput();
}

bool Game::notify(Command& c)
{
	Player *p = players_[nextPlayer_];
	switch (c.type)
	{
		case Command::Type::PLAY:
			if (isLegalMove(c.card) && p->play(c.card))
			{
				curRank_ = c.card.rank();
				curSuit_ = c.card.suit();
			}
			else
			{
				// output error message
				return true;
			}
			break;
		case Command::Type::DISCARD:
			if (p->discard(c.card))
			{
				// must play legal card instead of discarding
			}
			break;
		case Command::Type::DECK:
		{
			std::vector<std::string> cards(std::move(deck_.getCards()));
			view_->printDeck(cards);
			break;
		}
		case Command::Type::RAGEQUIT:
		{
			Player *temp = p;
			p = new ComputerPlayer(std::move(p->getHand()));
			delete temp;
			p->makeNextMove(curSuit_, curRank_);
			break;
		}
		case Command::Type::QUIT:
			return false;
		default:
			break;
	}

	// rotate and make computer player moves until we find the next human player
	for (size_t i = nextPlayer_; i < players_.size(); ++i)
	{
		if (players_[i]->isHuman() == false)
		{
			players_[i]->makeNextMove(curSuit_, curRank_);
		}
		else
		{
			nextPlayer_ = i;
			return true;
		}
	}

	for (size_t i = 0; i < nextPlayer_; ++i)
	{
		if (players_[i]->isHuman() == false)
		{
			players_[i]->makeNextMove(curSuit_, curRank_);
		}
		else
		{
			nextPlayer_ = i;
			break;
		}
	}
	return true;
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
