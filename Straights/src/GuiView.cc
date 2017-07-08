#include "GuiView.h"
#include "Game.h"

GuiView::GuiView(GameController *controller, Game *game) : Gtk::Window(), controller_(controller), game_(game),
														   toolBarBox_(Gtk::ORIENTATION_HORIZONTAL), tableBox_(), playersBox_(), handBox_(),
														   windowPanels_(Gtk::ORIENTATION_VERTICAL), startNewGame_("Start New Game"),
														   endGame_("End Game")
{
	if (nullptr != game_)
	{
		game_->subscribe(this);
	}

	set_title("Straights");
    set_border_width(10);
	set_default_size(500, 400);

	add(windowPanels_);
	windowPanels_.pack_start(toolBarBox_, Gtk::PACK_EXPAND_WIDGET);
	windowPanels_.pack_start(tableBox_, Gtk::PACK_EXPAND_WIDGET);
	windowPanels_.pack_start(playersBox_, Gtk::PACK_EXPAND_WIDGET);
	windowPanels_.pack_start(handBox_, Gtk::PACK_EXPAND_WIDGET);

	toolBarBox_.pack_start(startNewGame_, Gtk::PACK_EXPAND_WIDGET);
	toolBarBox_.pack_start(endGame_, Gtk::PACK_EXPAND_WIDGET);
	
	show_all();
}

GuiView::~GuiView() {}

void GuiView::init()
{
	game_->init();
	game_->beginRound();
	if (game_->isOver() == true)
	{
		return;
	}
}

void GuiView::showMessage(std::string message) const
{
	std::cout << message << std::endl;
}

void GuiView::showError(std::string error) const
{
	std::cout << error << std::endl;
}

void GuiView::showPlayerPlay(int id, std::string card) const
{
	std::cout << "Player " << std::to_string(id) << " plays " << card + "." << std::endl;
}

void GuiView::showPlayerDiscard(int id, std::string card) const
{
	std::cout << "Player " << std::to_string(id) << " discards " << card + "." << std::endl;
}

void GuiView::printDeck(const std::vector<std::string>& cards) const
{
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 13; ++j)
		{
			if (j != 0)
			{
				std::cout << " ";
			}
			std::cout << cards[13 * i + j];
		}
		std::cout << std::endl;
	}
}

void GuiView::showCardList(std::string label, std::vector<std::string>& cards) const
{
	std::string cardsIDs = label + ":";
	for (size_t i = 0; i < cards.size(); ++i)
	{
		cardsIDs += " " + cards[i];
	}

	std::cout << cardsIDs << std::endl;
}

// checking inital input 
// i.e. 'c' for computer, 'h' for human
bool GuiView::isPlayerHuman() const
{
	char c;
	std::cout << ">";
	std::cin >> c;

	if (std::cin.fail())
	{
		std::cin.clear();
		return true;
	}
	else 
	{
		if (c == 'c')
		{
			return false;
		}

		return true;
	}
}

// get input from a human player
void GuiView::getUserInput()
{
	std::cin.ignore();
	while (true)
	{
		Command c;
		std::cout << ">";
		
		try
		{
			std::cin >> c;
		}
		catch (Command::CommandException &e)
		{
			std::cout << e.what() << std::endl;
		}
		
		if (std::cin.fail())
		{
			break;
		}

		if (controller_->processCommand(c) == false)
		{
			break;
		}
	}
}
