#pragma once
#include "Player.h"

class ComputerPlayer : public Player
{
public:
	ComputerPlayer();
	ComputerPlayer(std::vector<Card *>&, std::vector<Card *>&);
	ComputerPlayer(std::vector<Card *>&&, std::vector<Card *>&&);
	virtual ~ComputerPlayer();
	bool isHuman() const override;
};

