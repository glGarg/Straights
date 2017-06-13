#pragma once
#include "Player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer();
	virtual ~HumanPlayer();
	bool isHuman() const override;
};
