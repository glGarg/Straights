#include "HandControl.h"
#include "GuiView.h"
#include "DeckGui.h"

HandControl::HandControl(GuiView *view, int playerIndex) : Gtk::Box(Gtk::ORIENTATION_VERTICAL), view_(view), cardBoxes_(13), cardButtons_(13), cardImages_(13),
                                                           handBox_(Gtk::ORIENTATION_HORIZONTAL), playerLabel_("Player " + std::to_string(playerIndex) + "'s hand")
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
    }
}
