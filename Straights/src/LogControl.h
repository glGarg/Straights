#pragma once
#include <gtkmm.h>

class GuiView;

class LogControl : public Gtk::Frame
{
public:
    LogControl(GuiView *);
    ~LogControl();
    void reset();
    void appendText(std::string);
private:
    void updateTextView();
    Gtk::ScrolledWindow scrolledWindow_;
    Gtk::TextView textView_;
    std::string text_;
    GuiView *view_;
    Glib::RefPtr<Gtk::TextBuffer> buffer_;
};
