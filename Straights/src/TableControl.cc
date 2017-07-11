#include "TableControl.h"
#include "GuiView.h"

TableControl::TableControl(GuiView *view, DeckGui *deckGui) : Gtk::Frame("Cards on the table"), tableBox_(Gtk::ORIENTATION_VERTICAL),
															  view_(view), deckGui_(deckGui),
                                            				  suitRows_{new Gtk::Box(), new Gtk::Box(),
											          					new Gtk::Box(), new Gtk::Box()}
{
    for (int i = 0; i < 4; ++i)
	{
		tableBox_.pack_start(*suitRows_[i], Gtk::PACK_EXPAND_WIDGET);
		suitRows_[i]->set_spacing(5);
	}
    
    for (int i = 0; i < Card::ranks.size(); ++i)
	{
		for (int j = 0; j < Card::suits.size(); ++j)
		{
			const std::string card = std::string(1, Card::ranks[i]) + std::string(1, Card::suits[j]);
			cardImages_[card] = new Gtk::Image();
		}
	}

	add(tableBox_);
}

TableControl::~TableControl()
{
    for (auto iter = cardImages_.begin(); iter != cardImages_.end(); iter++)
	{
		delete iter->second;
	}

    for (int i = 0; i < 4; ++i)
	{
		delete suitRows_[i];
	}
}

void TableControl::initTable()
{
	for (int i = 0; i < Card::ranks.size(); ++i)
	{
		for (int j = 0; j < Card::suits.size(); ++j)
		{
			const std::string card = std::string(1, Card::ranks[i]) + std::string(1, Card::suits[j]);
			cardImages_[card]->set((*deckGui_)["nothing"]);
			suitRows_[j]->pack_start(*cardImages_[card]);
		}
	}
}

void TableControl::showCard(std::string card)
{
	cardImages_[card]->set((*deckGui_)[card]);
}
