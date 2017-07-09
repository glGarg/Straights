#include "HandControl.h"
#include "GuiView.h"
#include "DeckGui.h"

HandControl::HandControl(GuiView *view, int playerIndex) : Gtk::Box(Gtk::ORIENTATION_VERTICAL), view_(view), cardBoxes_(13), cardButtons_(13), cardImages_(13), cardConnections_(13), index_(playerIndex),
                                                           handBox_(Gtk::ORIENTATION_HORIZONTAL), playerLabel_("Player " + std::to_string(playerIndex + 1) + "'s hand")
{
    for (int i = 0; i < 13; ++i)
	{
		cardBoxes_[i] = new Gtk::Box();
        cardButtons_[i] = new Gtk::Button();
        cardImages_[i] = new Gtk::Image();
        cardButtons_[i]->set_image(*cardImages_[i]);
        cardBoxes_[i]->pack_start(*cardButtons_[i]);
        handBox_.pack_start(*cardBoxes_[i]);
	}

    pack_start(playerLabel_);
    pack_start(handBox_);
}

HandControl::~HandControl()
{
    for (int i = 0; i < 13; ++i)
	{
        delete cardImages_[i];
		delete cardBoxes_[i];
		delete cardButtons_[i];
	}
}

void HandControl::setHand(std::vector<std::string>& hand, DeckGui *deckGui)
{
    for (int i = 0; i < hand.size(); ++i)
    {
        cardImages_[i]->set((*deckGui)[hand[i]]);
        cardButtons_[i]->set_sensitive(true);
        cardConnections_[i].disconnect();
        cardConnections_[i] = cardButtons_[i]->signal_clicked().connect(sigc::bind<std::string, Gtk::Button *>(sigc::mem_fun(*this, &HandControl::playCard), hand[i], cardButtons_[i]));
    }
}

void HandControl::playCard(std::string card, Gtk::Button *button)
{
    std::vector<std::string> legalPlays(std::move(view_->getPlayerLegalPlays(index_)));
    for (int i = 0; i < legalPlays.size(); ++i)
    {
        if (legalPlays[i] == card)
        {
            view_->playerPlayedCard(card);
            if(nullptr != button)
            {
                button->set_sensitive(false);
            }
            
            return;
        }
    }

    if(nullptr != button && legalPlays.size() == 0)
    {
        button->set_sensitive(false);
    }
    view_->playerDiscardedCard(card);
}

void HandControl::highlightLegalPlays(std::vector<std::string>& hand, std::vector<std::string>& legalPlays) {}
