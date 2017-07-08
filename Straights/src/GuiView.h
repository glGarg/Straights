#pragma once
#include "View.h"
#include "DeckGui.h"
#include "PlayerControl.h"
#include "HandControl.h"
#include "ToolBarControl.h"
#include "TableControl.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm.h>

class GuiView : public View, public Gtk::Window
{
public:
	GuiView(GameController *, Game *);
	~GuiView();
	void init() override;
	void initPlayerControls();
	void showMessage(std::string) const override;
	void showError(std::string) const override;
	void showPlayerPlay(int, std::string) const override;
	void showPlayerDiscard(int, std::string) const override;
	void printDeck(const std::vector<std::string>&) const override;
	void showCardList(std::string, std::vector<std::string>&) const override;
	bool isPlayerHuman() const override;
	void getUserInput() override;
	void playerRageQuit(int) const;
private:
	GameController *controller_;
	Game *game_;
	DeckGui *deckGui_;
	Gtk::Box handBox_;
	std::vector<HandControl *> handControls_;
	Gtk::Box windowPanels_;
	Gtk::Box playersBox_;
	std::vector<PlayerControl *> playerControls_;
	TableControl tableControl_;
	ToolBarControl toolBarControl_;
};
