#include "Game.h"
#include <algorithm>

namespace
{
	void print(std::string msg)
	{
		std::cout << msg << std::endl;
	}
}

Game::Game() : Subject(), players_(4), playerScores_(PLAYER_COUNT), nextPlayer_(0), lastPlayer_(0) {}

bool Game::firstTurn_ = true, Game::isOver_ = false, Game::newGameStarted_ = true;

const int Game::PLAYER_COUNT = 4;

std::map<Card::Suit, std::vector<Card>> Game::cardsPlayed_ = std::map<Card::Suit, std::vector<Card>> {{Card::Suit(0), {}}, 
																									  {Card::Suit(1), {}},
																									  {Card::Suit(2), {}}, 
																									  {Card::Suit(3), {}}};

void Game::init()
{
	if (newGameStarted_ == true)
	{
		for (int i = 0; i < PLAYER_COUNT; ++i)
		{
			if (nullptr != players_[i])
			{
				delete players_[i];
			}
			
			if (isPlayerHuman(i + 1))
			{
				players_[i] = new HumanPlayer();
			}
			else
			{
				players_[i] = new ComputerPlayer();
			}
		}

		newGameStarted_ = false;
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
	lastPlayer_ = (nextPlayer_ + PLAYER_COUNT - 1) % 4;
}

void Game::beginRound()
{
	showMessage("A new round begins. It's player " + std::to_string(nextPlayer_ + 1) + "'s turn to play.");
	if (players_[nextPlayer_]->isHuman())
	{
		displayGameState();
	}
	else
	{
		decideNextPlayer();
	}

	if (isLastPlayerHandEmpty() == true)
	{
		tallyScores();
	}
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

// human player plays a card
void Game::playCard(Card& card)
{
	Player *p = players_[nextPlayer_];
	if (isLegalMove(card) && p->play(card))
	{
		cardsPlayed_[card.suit()].insert(std::upper_bound(cardsPlayed_[card.suit()].begin(), cardsPlayed_[card.suit()].end(), card), card);
		showPlayerPlay(nextPlayer_ + 1, card);
		firstTurn_ = false;
		decideNextPlayer();
	}
	else
	{
		showError("This is not a legal play.");
	}
}

// human player discards a card
void Game::discardCard(Card& card)
{
	Player *p = players_[nextPlayer_];
	std::vector<Card *> hand = p->getHand();
	for (size_t i = 0; i < hand.size(); ++i)
	{
		if (isLegalMove(*hand[i]))
		{
			showError("You have a legal play. You may not discard.");
			return;
		}
	}

	if (p->discard(card) == true)
	{
		showPlayerDiscard(nextPlayer_ + 1, std::string(card));
		decideNextPlayer();
	}
	else
	{
		throw IllegalDiscardException(card);
	}

}

void Game::printDeck() const
{
	std::vector<std::string> cards(std::move(deck_.getCards()));
	printCards(cards);
}

// human player ragequits; replace them with a computer player
void Game::rageQuit()
{
	Player *temp = players_[nextPlayer_];
	players_[nextPlayer_] = new ComputerPlayer(std::move(temp->getHand()), std::move(temp->getDiscardPile()));
	delete temp;
	showMessage("Player " + std::to_string(nextPlayer_ + 1) + " ragequits. A computer will now take over.");
	decideNextPlayer();
}

void Game::restartGame()
{
	newGameStarted_ = true;
	isOver_ = false;
	for (auto &i : cardsPlayed_)
	{
		i.second.clear();
	}

	for (int i = 0; i < PLAYER_COUNT; ++i)
	{
		players_[i]->reset();
		playerScores_[i] = 0;
	}
}

bool Game::isLastPlayerHandEmpty() const
{
	return players_[lastPlayer_]->isHandEmpty();
}

// sum up the scores at the end of a round
// end the game if score limit is reached
void Game::tallyScores()
{
	for (size_t i = 0; i < players_.size(); ++i)
	{
		std::vector<std::string> discardPile = players_[i]->getDiscardPileStr();
		showCardList("Player " + std::to_string(i + 1) + "'s discards", discardPile);

		int oldScore = playerScores_[i];
		int scoreGained = players_[i]->getScore();
		int newScore = oldScore + scoreGained;

		showMessage("Player " + std::to_string(i + 1) + "'s score: " + std::to_string(oldScore) +
			" + " + std::to_string(scoreGained) + " = " + std::to_string(newScore));

		playerScores_[i] = newScore;
		if (isOver_ == false)
		{
			isOver_ = playerScores_[i] >= 80;
		}
	}

	if (isOver_)
	{
		std::vector<int> lowestScoreIndices = { 0 };
		for (size_t i = 1; i < players_.size(); ++i)
		{
			if (playerScores_[i] < playerScores_[lowestScoreIndices[0]])
			{
				lowestScoreIndices.clear();
				lowestScoreIndices.push_back(i);
			}
			else if (playerScores_[i] == playerScores_[lowestScoreIndices[0]])
			{
				lowestScoreIndices.push_back(i);
			}
		}

		showWinners(lowestScoreIndices);
	}
	else
	{
		resetRound();
	}
}

bool Game::isOver() const
{
	return isOver_;
}

int Game::getNextPlayerIndex() const
{
	return nextPlayer_;
}

bool Game::isPlayerIndexHuman(int index) const
{
	return players_[index]->isHuman();
}

std::vector<std::string> Game::getPlayerHandStr(int index) const
{
	return players_[index]->getHandStr();
}

void Game::decideNextPlayer()
{
	bool wrapped = false;
	for (size_t i = players_[nextPlayer_]->isHuman() ? ((nextPlayer_ + 1) % 4) : nextPlayer_;
		 i != nextPlayer_ || !wrapped || !players_[i]->isHuman();
		 ++i)
	{
		if (isLastPlayerHandEmpty())
		{
			return;
		}

		if (i == players_.size())
		{
			i = 0;
			wrapped = true;
		}

		if (players_[i]->isHuman() == false)
		{
			Card *discardedCard = nullptr;
			const Card *cardPlayed = players_[i]->makeNextMove(discardedCard);
			if (nullptr != cardPlayed)
			{
				cardsPlayed_[cardPlayed->suit()].push_back(*cardPlayed);
				showPlayerPlay(i + 1, *cardPlayed);
				firstTurn_ = false;
			}
			else if (nullptr != discardedCard)
			{
				showPlayerDiscard(i + 1, *discardedCard);
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

void Game::resetRound()
{
	init();
	firstTurn_ = true;
	for (auto &iter : cardsPlayed_)
	{
		iter.second.erase(iter.second.begin(), iter.second.end());
	}

	for (int i = 0; i < PLAYER_COUNT; ++i)
	{
		players_[i]->reset();
	}

	resetDisplay();
	beginRound();
}

bool Game::isLegalMove(Card &c)
{
	if (((firstTurn_ && c.suit().suit() == Card::Suit::SPADE) || !firstTurn_) && c.rank().rank() == Card::Rank::SEVEN)
	{
		return true;
	}
	else
	{
		for (auto &iter : cardsPlayed_)
		{
			for (size_t i = 0; i < iter.second.size(); ++i)
			{
				if (c.suit() == iter.second[i].suit() &&
				   ((iter.second[i].rank() != 0 && c.rank() == Card::Rank(iter.second[i].rank() - 1)) ||
				    (iter.second[i].rank() != 12 && c.rank() == Card::Rank(iter.second[i].rank() + 1))))
				{
					return true;
				}
			}
		}
	}

	return false;
	
}

// provide human player with information about the current game state
void Game::displayGameState() const
{
	showMessage("Cards on the table:");

	for (auto &iter : cardsPlayed_)
	{
		std::vector<std::string> cardsInSuit;
		for (size_t i = 0; i < iter.second.size(); ++i)
		{
			cardsInSuit.emplace_back(std::string(1, Card::ranks[iter.second[i].rank()]));
		}
		showCardList(iter.first.toString(), cardsInSuit);
	}

	std::vector<Card *> cardsInHand = players_[nextPlayer_]->getHand();
	std::vector<std::string> hand, legalPlays = getPlayerLegalPlays(nextPlayer_);
	for (size_t i = 0; i < cardsInHand.size(); ++i) { hand.push_back(*cardsInHand[i]); }
	
	showCardList("Your hand", hand);
	showCardList("Legal plays", legalPlays);
	updateDisplay();
}

std::vector<std::string> Game::getPlayerLegalPlays(int id) const
{
	std::vector<std::string> legalPlays;
	std::vector<Card *> cardsInHand = players_[id]->getHand();
	for (size_t i = 0; i < cardsInHand.size(); ++i)
	{
		if (isLegalMove(*cardsInHand[i]))
		{
			legalPlays.push_back(std::string(*cardsInHand[i]));
		}
	}

	return legalPlays;
}

Game::GameException::GameException(const std::string message) : message_(message) {}

std::string Game::GameException::what() const { return message_; }

Game::IllegalDiscardException::IllegalDiscardException(Card& card) : GameException("Your hand doesn't contain " + std::string(card) + ".") {}