#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer() {}

ComputerPlayer::ComputerPlayer(std::vector<Card *>& hand, std::vector<Card *>& discardPile) : Player(hand, discardPile) {}

ComputerPlayer::ComputerPlayer(std::vector<Card *>&& hand, std::vector<Card *>&& discardPile) : Player(std::move(hand), std::move(discardPile)) {}

ComputerPlayer::~ComputerPlayer() {}

bool ComputerPlayer::isHuman() const { return false; }