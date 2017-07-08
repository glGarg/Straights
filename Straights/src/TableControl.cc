#include "TableControl.h"
#include "GuiView.h"

TableControl::TableControl(GuiView *view) : Gtk::Box(Gtk::ORIENTATION_VERTICAL), view_(view),
                                            suitRows_{new Gtk::Box(), new Gtk::Box(),
											          new Gtk::Box(), new Gtk::Box()}
{
    for (int i = 0; i < 4; ++i)
	{
		pack_start(*suitRows_[i], Gtk::PACK_EXPAND_WIDGET);
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

void TableControl::initTable(DeckGui *deckGui)
{
	for (int i = 0; i < Card::ranks.size(); ++i)
	{
		for (int j = 0; j < Card::suits.size(); ++j)
		{
			const std::string card = std::string(1, Card::ranks[i]) + std::string(1, Card::suits[j]);
			cardImages_[card]->set((*deckGui)[card]);
			suitRows_[j]->pack_start(*cardImages_[card]);
		}
	}
}
