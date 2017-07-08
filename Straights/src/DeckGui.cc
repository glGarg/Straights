#include "DeckGui.h"
#include "Card.h"
#include <string>
using std::string;

namespace
{
    Glib::RefPtr<Gdk::Pixbuf> createPixbuf (const string name)
    {
        return Gdk::Pixbuf::create_from_file(name);
    }
}

DeckGui::DeckGui()
{
    for(int i = 0; i < Card::suits.size(); ++i)
    {
        for(int j = 0; j < Card::ranks.size(); ++j)
        {
            const string card = string(1, Card::ranks[j]) + string(1, Card::suits[i]);
            deck_[card] = createPixbuf("../assets/img/" + card + ".png");
        }
    }
    deck_["nothing"] = createPixbuf("../assets/img/nothing.png");
}

DeckGui::~DeckGui() {}

const Glib::RefPtr<Gdk::Pixbuf> DeckGui::getCardImage(string card) const
{
    return deck_.at(card);
}

const Glib::RefPtr<Gdk::Pixbuf> DeckGui::operator[](string card) const
{
    return deck_.at(card);
}
