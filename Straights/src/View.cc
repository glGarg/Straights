#include "View.h"

View::View(GameController *controller, Game *game) : Observer(), controller_(controller), game_(game)
{
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
