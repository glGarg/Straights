#include "Game.h"

Game::Game() : Subject(), PLAYER_COUNT(4), firstTurn_(true), players_(PLAYER_COUNT), curRank_(Card::Rank::SEVEN),
			   curSuit_(Card::Suit::SPADE), nextPlayer_(0), cardsPlayed_{{Card::Suit(0), {}}, {Card::Suit(1), {}},
																		 {Card::Suit(2), {}}, {Card::Suit(3), {}}} {}

void Game::init()
{
	for (int i = 0; i < PLAYER_COUNT; ++i)
	{
		if (isPlayerHuman(i + 1))
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

	nextPlayer_ = playerWith7OfSpades;
	notify("A new round begins. It's player " + std::to_string(nextPlayer_ + 1) + "'s turn to play.");
	decideNextPlayer();
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
		cardsPlayed_[curSuit_].emplace_back(card);
		notify("Player " + std::to_string(nextPlayer_ - 1) + " plays " + std::string(card) + ".");
		firstTurn_ = false;
		decideNextPlayer();
	}
	else
	{
		notify("This is not a legal play.");
	}
}

void Game::discardCard(Card& card)
{
	Player *p = players_[nextPlayer_];
	if (p->discard(card) == true)
	{
		notify("Player " + std::to_string(nextPlayer_ - 1) + " discards " + std::string(card) + ".");
		decideNextPlayer();
	}
	else
	{
		notify("You have a legal play. You may not discard.");
	}
}

void Game::printDeck() const
{
	std::vector<std::string> cards(std::move(deck_.getCards()));
	notify(cards);
}

void Game::rageQuit()
{
	Player *p = players_[nextPlayer_];
	Player *temp = p;
	p = new ComputerPlayer(std::move(p->getHand()));
	delete temp;
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
				firstTurn_ = false;
			}
		}
		else
		{
			nextPlayer_ = i;
			break;
		}
	}
	displayGameState();
}

bool Game::isLegalMove(Card &c) const
{
	if (c.rank() == curRank_ && (firstTurn_ == true && c.suit() == curSuit_ || firstTurn_ == false) ||
	   (c.suit() == curSuit_ && ((curRank_.rank() != 0 && c.rank() == Card::Rank(curRank_.rank() - 1)) ||
	   (curRank_.rank() != 12 && c.rank() == Card::Rank(curRank_.rank() + 1)))))
	{
		return true;
	}
	return false;
}

void Game::displayGameState() const
{
	notify("Cards on the table:");

	for (auto &iter : cardsPlayed_)
	{
		std::string cardsInSuit = iter.first.toString() + ":";

		for (size_t i = 0; i < iter.second.size(); ++i)
		{
			cardsInSuit += " " + Card::ranks[iter.second[i].rank().rank()];
		}

		notify(cardsInSuit);
	}

	std::vector<Card *> hand = players_[nextPlayer_]->getHand();
	std::string legalPlays = "Legal plays:", yourHand = "Your hand:";

	for (size_t i = 0; i < hand.size(); ++i)
	{
		yourHand += " " + std::string(*hand[i]);
		
		if (isLegalMove(*hand[i]))
		{
			legalPlays += " " + std::string(*hand[i]);
		}
	}

	notify(yourHand + '\n' + legalPlays);
}
