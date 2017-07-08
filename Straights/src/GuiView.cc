#include "GuiView.h"
#include "Game.h"

GuiView::GuiView(GameController *controller, Game *game) : Gtk::Window(), controller_(controller), game_(game),
														   playersBox_(), handBox_(), windowPanels_(Gtk::ORIENTATION_VERTICAL), deckGui_(new DeckGui()), 
														   toolBarControl_(this), tableControl_(this), handControls_(4),
														   playerControls_{new PlayerControl(this, 0), new PlayerControl(this, 1),
														   				   new PlayerControl(this, 2), new PlayerControl(this, 3)}
{
	if (nullptr != game_)
	{
		game_->subscribe(this);
	}

	set_title("Straights");
    set_border_width(10);
	set_default_size(500, 550);

	add(windowPanels_);
	windowPanels_.pack_start(toolBarControl_, Gtk::PACK_EXPAND_WIDGET);
	windowPanels_.pack_start(tableControl_, Gtk::PACK_EXPAND_WIDGET);
	windowPanels_.pack_start(playersBox_, Gtk::PACK_EXPAND_WIDGET);
	windowPanels_.pack_start(handBox_, Gtk::PACK_EXPAND_WIDGET);

	for (int i = 0; i < 4; ++i)
	{
		playersBox_.pack_start(*playerControls_[i]);
	}

	initPlayerControls();
	tableControl_.initTable(deckGui_);
}

void GuiView::initPlayerControls() {}

GuiView::~GuiView()
{
	for (int i = 0; i < 4; ++i)
	{
		delete playerControls_[i];
	}

	delete deckGui_;
}

void GuiView::init()
{
	game_->init();
	game_->beginRound();
	if (game_->isOver() == true)
	{
		return;
	}

	show_all();

	for(int i = 0; i < 4; ++i)
	{
		if(game_->isPlayerIndexHuman(i))
		{
			std::vector<std::string> hand = game_->getPlayerHandStr(i);
			handControls_[i] = new HandControl(this, i);
			handControls_[i]->setHand(hand, deckGui_);
			handControls_[i]->hide();
			handBox_.pack_start(*handControls_[i]);
		}
	}

	handControls_[game_->getNextPlayerIndex()]->show_all();
	handBox_.show();
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

bool GuiView::isPlayerHuman() const
{
	static int index = 0;
	Gtk::MessageDialog dialog("Is player " + std::to_string(index) + " human?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
	dialog.set_secondary_text("");
	index = (index + 1) % 4;

	int result = dialog.run();
	switch(result)
	{
		case(Gtk::RESPONSE_YES):
		{
			return true;
		}
		default:
		{
			return false;
		}
	}
	return true;
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

void GuiView::playerRageQuit(int playerId) const
{
	Command c = Command(Command::Type::RAGEQUIT, Card(0, 0));
	controller_->processCommand(c);
}
