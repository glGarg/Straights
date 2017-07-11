#pragma once
#include <map>
#include <vector>
#include <gtkmm.h>

class DeckGui;
class GuiView;

class TableControl : public Gtk::Frame
{
public:
    TableControl(GuiView *, DeckGui *);
    ~TableControl();
    void initTable();
    void showCard(std::string);
private:
    Gtk::Box tableBox_;
    std::map<std::string, Gtk::Image *> cardImages_;
	std::vector<Gtk::Box *> suitRows_;
    GuiView *view_;
    DeckGui *deckGui_;
};
