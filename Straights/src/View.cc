#include "View.h"
#include "Game.h"

View::View(GameController *controller, Game *game) : controller_(controller), game_(game)
{
	if (nullptr != game_) 
	{
		game_->subscribe(this);
	}
	getUserInput();
}

View::~View() {}

void View::getUserInput()
{
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
			return;
		}
	}
}
