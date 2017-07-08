#pragma once
#include <gdkmm/pixbuf.h>
#include <map>

class DeckGui
{
public:
    DeckGui();
    ~DeckGui();
    const Glib::RefPtr<Gdk::Pixbuf> getCardImage(std::string) const;
    const Glib::RefPtr<Gdk::Pixbuf> operator[](std::string) const;
private:
    std::map<std::string, Glib::RefPtr<Gdk::Pixbuf>> deck_;
};
