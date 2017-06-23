#pragma once
#include <iostream>
#include <string>

struct Command;
class Game;

class GameController
{
public:
	GameController(Game *);
	~GameController();
	bool processCommand(Command&);
private:
	Game *model_;
};
