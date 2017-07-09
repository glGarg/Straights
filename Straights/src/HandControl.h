#pragma once
#include <vector>
#include <gtkmm.h>

class DeckGui;
class GuiView;

class HandControl : public Gtk::Box
{
public:
    HandControl(GuiView *, int);
    ~HandControl();
    void setHand(std::vector<std::string>&, DeckGui *);
    void playCard(std::string, Gtk::Button *);
    void highlightLegalPlays(std::vector<std::string>&, std::vector<std::string>&);
private:
    int index_;
    Gtk::Label playerLabel_;
    Gtk::Box handBox_;
    std::vector<Gtk::Box *> cardBoxes_;
    std::vector<Gtk::Button *> cardButtons_;
    std::vector<Gtk::Image *> cardImages_;
	GuiView *view_;
};
