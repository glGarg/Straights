#pragma once
#include "ComputerPlayer.h"

class SmartComputerPlayer : public ComputerPlayer
{
public:
	SmartComputerPlayer();
	SmartComputerPlayer(std::vector<Card *>&, std::vector<Card *>&);
	SmartComputerPlayer(std::vector<Card *>&&, std::vector<Card *>&&);
	virtual ~SmartComputerPlayer();
	const Card *makeNextMove(Card *&) override;
};
