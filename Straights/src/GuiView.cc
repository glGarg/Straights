#include "GuiView.h"
#include "Game.h"
#include "Deck.h"

namespace
{
	void print(std::string message)
	{
		std::cout << message << std::endl;
	}
}

GuiView::GuiView(GameController *controller, Game *game) : Gtk::Window(), controller_(controller), game_(game), curHandControl_(nullptr), curPlayerControl_(nullptr),
														   playersBox_(), handBox_(), windowPanels_(Gtk::ORIENTATION_VERTICAL), deckGui_(new DeckGui()), 
														   toolBarControl_(this), tableControl_(this, deckGui_), handControls_(4),
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

	tableControl_.initTable();
}

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
	for (int i = 0; i < handControls_.size(); ++i)
	{
		if (nullptr != handControls_[i])
		{
			delete handControls_[i];
			handControls_[i] = nullptr;
		}
	}

	curHandControl_ = nullptr;
	game_->init();
	game_->beginRound();
	if (game_->isOver() == true)
	{
		//return;
	}

	show_all();

	for (int i = 0; i < handControls_.size(); ++i)
	{
		if (game_->isPlayerIndexHuman(i))
		{
			handControls_[i] = new HandControl(this, i);
			handBox_.pack_start(*handControls_[i]);
		}
	}

	initPlayerControls();
}

void GuiView::initPlayerControls()
{
	for (int i = 0; i < handControls_.size(); ++i)
	{
		if (game_->isPlayerIndexHuman(i) && nullptr != handControls_[i])
		{
			std::vector<std::string> hand = game_->getPlayerHandStr(i);
			handControls_[i]->setHand(hand, deckGui_);
			handControls_[i]->hide();
		}
	}

	size_t nextPlayerIndex = game_->getNextPlayerIndex();
	curHandControl_ = handControls_[nextPlayerIndex];
	if (nullptr != curHandControl_)
	{
		curHandControl_->show_all();
	}

	curPlayerControl_ = playerControls_[nextPlayerIndex];
	if (game_->isPlayerIndexHuman(nextPlayerIndex))
	{
		curPlayerControl_->enableRage();
	}

	handBox_.show();
}

void GuiView::showMessage(std::string message) const
{
	//Gtk::MessageDialog dialog(message, false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK);
	//dialog.set_secondary_text(message);
	//dialog.run();
	std::cout << message << std::endl;
}

void GuiView::showError(std::string error) const
{
	Gtk::MessageDialog dialog("Oops", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK);
	dialog.set_secondary_text(error);
	dialog.run();
	std::cout << error << std::endl;
}

void GuiView::showPlayerPlay(int id, std::string card)
{
	tableControl_.showCard(card);
	std::cout << "Player " << std::to_string(id) << " plays " << card + "." << std::endl;
}

void GuiView::showPlayerDiscard(int id, std::string card)
{
	std::cout << "Player " << std::to_string(id) << " discards " << card + "." << std::endl;
	playerControls_[id - 1]->setDiscardCount(playerControls_[id - 1]->getDiscardCount() + 1);
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

void GuiView::updateDisplay()
{
	if(curHandControl_ != nullptr)
	{
		curHandControl_->hide();
	}

	if(curPlayerControl_ != nullptr)
	{
		curPlayerControl_->disableRage();
	}

	size_t nextPlayerIndex = game_->getNextPlayerIndex();
	curHandControl_ = handControls_[nextPlayerIndex];
	curPlayerControl_ = playerControls_[nextPlayerIndex];
	if(nullptr != curHandControl_)
	{
		curHandControl_->show_all();
		if(nullptr != curPlayerControl_ && !curPlayerControl_->getRageQuit())
		{
			curPlayerControl_->enableRage();
		}
	}
}

bool GuiView::isPlayerHuman() const
{
	static int index = 0;
	Gtk::MessageDialog dialog("Is player " + std::to_string(index + 1) + " human?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
	dialog.set_secondary_text("");
	index = (index + 1) % 4;

	int result = dialog.run();
	switch (result)
	{
		case(Gtk::RESPONSE_YES):
			return true;
		default:
			return false;
	}
	return true;
}

void GuiView::getUserInput() {}

void GuiView::playerRageQuit(int playerId)
{
	Command c;
	c.type = Command::Type::RAGEQUIT;
	if(nullptr != curHandControl_)
	{
		delete curHandControl_;
		curHandControl_ = nullptr;
		handControls_[playerId] = nullptr;
	}

	controller_->processCommand(c);
}

void GuiView::playerPlayedCard(std::string card)
{
	Command c;
	c.type = Command::Type::PLAY;
	c.card = Card(Card::Rank(card[0]), Card::Suit(card[1]));
	controller_->processCommand(c);
}

void GuiView::quitGame()
{
	Command c;
	c.type = Command::Type::QUIT;
	c.card = Card(Card::Rank(0), Card::Suit(0));
	controller_->processCommand(c);
}

void GuiView::reset()
{
	for (int i = 0; i < 4; ++i)
	{
		if(nullptr != playerControls_[i])
		{
			playerControls_[i]->reset();
		}
	}

	curHandControl_ = nullptr;
	curPlayerControl_ = nullptr;
	tableControl_.initTable();
	initPlayerControls();
}

void GuiView::restartGameWithSeed(int newSeed)
{
	Command c;
	c.type = Command::Type::RESTART;
	c.card = Card(Card::Rank(0), Card::Suit(0));
	seed = newSeed;
	controller_->processCommand(c);
	reset();
	init();
}

void GuiView::playerDiscardedCard(std::string card)
{
	Command c;
	c.type = Command::Type::DISCARD;
	c.card = Card(Card::Rank(card[0]), Card::Suit(card[1]));
	controller_->processCommand(c);
}

std::vector<std::string> GuiView::getPlayerLegalPlays(int id) const { return game_->getPlayerLegalPlays(id); }

std::vector<std::string> GuiView::getPlayerHand(int id) const { return game_->getPlayerHandStr(id); }
