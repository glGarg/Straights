#pragma once
#include <gtkmm.h>

class GuiView;

class ToolBarControl : public Gtk::Frame
{
public:
    ToolBarControl(GuiView *);
    ~ToolBarControl();
    void startNewGame() const;
    void endGame() const;
private:
    Gtk::Box toolBarBox_;
    Gtk::Entry seedEntry_;
    Gtk::Button startNewGame_;
	Gtk::Button endGame_;
    GuiView *view_;
};
