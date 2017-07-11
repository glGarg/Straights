#include "SmartComputerPlayer.h"
#include "Game.h"

SmartComputerPlayer::SmartComputerPlayer() {}

SmartComputerPlayer::SmartComputerPlayer(std::vector<Card *>& hand, std::vector<Card *>& discardPile) : ComputerPlayer(hand, discardPile) {}

SmartComputerPlayer::SmartComputerPlayer(std::vector<Card *>&& hand, std::vector<Card *>&& discardPile) : ComputerPlayer(std::move(hand), std::move(discardPile)) {}

SmartComputerPlayer::~SmartComputerPlayer() {}

const Card *SmartComputerPlayer::makeNextMove(Card *&discarded)
{
    std::vector<Card *> hand = getHand();
    std::map<Card *, int> legalPlays;
    for (size_t i = 0; i < hand.size(); ++i)
	{
		if (Game::isLegalMove(*hand[i]))
		{
            legalPlays[hand[i]] = i;
		}
	}

    const Card *play = nullptr;
    int indexToRemove = 0;
    if (legalPlays.size() > 0)
    {
        // find the largest card to play
        play = legalPlays.begin()->first;
        indexToRemove = legalPlays.begin()->second;
        for (auto &c : legalPlays)
        {
            if(c.first->rank() > play->rank())
            {
                play = c.first;
                indexToRemove = c.second;
            }
        }
    }
    else
    {
        // find the smallest card to discard
        Card *discard = hand[0];
        for (int i = 0; i < hand.size(); ++i)
        {
            if (hand[i]->rank() < discard->rank())
            {
                discard = hand[i];
                indexToRemove = i;
            }
        }

        addCardToDiscardPile(discard);
        discarded = discard;
    }

    removeCardFromHand(indexToRemove);
    return play;
}
