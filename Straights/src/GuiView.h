#pragma once
#include "View.h"
#include "DeckGui.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm.h>

class GuiView : public View, public Gtk::Window
{
public:
	GuiView(GameController *, Game *);
	~GuiView();
	void init() override;
	void initTable();
	void showMessage(std::string) const override;
	void showError(std::string) const override;
	void showPlayerPlay(int, std::string) const override;
	void showPlayerDiscard(int, std::string) const override;
	void printDeck(const std::vector<std::string>&) const override;
	void showCardList(std::string, std::vector<std::string>&) const override;
	bool isPlayerHuman() const override;
	void getUserInput() override;
private:
	GameController *controller_;
	Game *game_;
	std::map<std::string, Gtk::Image *> cardImages_;
	DeckGui deckGui_;
	Gtk::Box windowPanels_;
	Gtk::Box toolBarBox_;
	std::vector<Gtk::Box *> suitRows_;
	Gtk::Box tableBox_;
	Gtk::Box playersBox_;
	Gtk::Box handBox_;
	Gtk::Button startNewGame_;
	Gtk::Button endGame_;
};
