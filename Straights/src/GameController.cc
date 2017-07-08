#include "GameController.h"
#include "Game.h"
#include "Command.h"

GameController::GameController(Game *model) : model_(model) {}

GameController::~GameController() {}

bool GameController::processCommand(Command& c)
{
	try
	{
		switch (c.type)
		{
		case Command::Type::PLAY:
			model_->playCard(c.card);
			break;
		case Command::Type::DISCARD:
			model_->discardCard(c.card);
			break;
		case Command::Type::DECK:
			model_->printDeck();
			break;
		case Command::Type::RAGEQUIT:
			model_->rageQuit();
			break;
		case Command::Type::QUIT:
			return false;
		default:
			break;
		}
	}
	catch (Game::GameException &e)
	{
		std::cout << e.what() << std::endl;
	}

	if (model_->isLastPlayerHandEmpty())
	{
		model_->tallyScores();
		return !model_->isOver();
	}

	return true;
}
