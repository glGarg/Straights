#pragma once
#include <gtkmm.h>

class GuiView;

class PlayerControl : public Gtk::Frame
{
public:
    PlayerControl(GuiView *, int);
    ~PlayerControl();
    void reset();
    void rageQuit();
    bool getRageQuit() const;
    void enableRage();
    void disableRage();
    void setDiscardCount(int);
    int getDiscardCount() const;
    void setScore(int);
private:
    void updateLabel();
    Gtk::Box playerBox_;
    Gtk::Button rage_;
    bool playerRageQuit_;
    Gtk::Label info_;
    int playerIndex_;
    int discardCount_;
    int score_;
    GuiView *view_;
};
