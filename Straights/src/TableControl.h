#pragma once
#include <map>
#include <vector>
#include <gtkmm.h>

class DeckGui;
class GuiView;

class TableControl : public Gtk::Box
{
public:
    TableControl(GuiView *);
    ~TableControl();
    void initTable(DeckGui *);
private:
    std::map<std::string, Gtk::Image *> cardImages_;
	std::vector<Gtk::Box *> suitRows_;
    GuiView *view_;
};
