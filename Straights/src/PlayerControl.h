#pragma once
#include <gtkmm.h>

class GuiView;

class PlayerControl : public Gtk::Box
{
public:
    PlayerControl(GuiView *, int);
    ~PlayerControl();
    void rageQuit();
    void enableRage();
    void disableRage();
    void setDiscardCount(int);
    int getDiscardCount() const;
private:
    Gtk::Label playerId_;
    Gtk::Button rage_;
    Gtk::Label info_;
    int playerIndex_;
    int discardCount_;
    int score_;
    GuiView *view_;
};
