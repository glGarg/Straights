#include "View.h"
#include "Game.h"

View::View(GameController *controller, Game *game) : controller_(controller), game_(game)
{
	if (nullptr != game_) 
	{
		game_->subscribe(this);
	}
}

View::~View() {}

void View::init()
{
	if (game_->init() == false)
	{
		return;
	}

	getUserInput();
}

void View::getUserInput()
{
	std::cin.ignore();
	while (true)
	{
		Command c;
		std::cin >> c;
		if (std::cin.fail())
		{
			break;
		}
		if(controller_->processCommand(c) == false)
		{
			break;
		}
	}
}
