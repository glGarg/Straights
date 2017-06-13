#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer() {}

ComputerPlayer::ComputerPlayer(std::vector<Card *>& hand) : Player(hand) {}

ComputerPlayer::ComputerPlayer(std::vector<Card *>&& hand) : Player(std::move(hand)) {}

ComputerPlayer::~ComputerPlayer() {}

bool ComputerPlayer::isHuman() const { return false; }