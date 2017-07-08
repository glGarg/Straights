#pragma once
#include <gtkmm.h>

class GuiView;

class ToolBarControl : public Gtk::Box
{
public:
    ToolBarControl(GuiView *);
    ~ToolBarControl();
private:
    void startNewGame() const;
    void endGame() const;
    Gtk::Entry seedEntry_;
    Gtk::Button startNewGame_;
	Gtk::Button endGame_;
    GuiView *view_;
};
