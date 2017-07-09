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
	void showPlayerPlay(int, std::string) override;
	void showPlayerDiscard(int, std::string) override;
	void printDeck(const std::vector<std::string>&) const override;
	void showCardList(std::string, std::vector<std::string>&) const override;
	bool isPlayerHuman() const override;
	void getUserInput() override;
	std::vector<std::string> getPlayerLegalPlays(int) const;
	std::vector<std::string> getPlayerHand(int) const;

	//Gameplay functions
	void playerRageQuit(int);
	void playerPlayedCard(std::string);
	void playerDiscardedCard(std::string);
	void quitGame();
	void updateDisplay();
private:
	GameController *controller_;
	Game *game_;
	DeckGui *deckGui_;
	Gtk::Box handBox_;
	std::vector<HandControl *> handControls_;
	HandControl *curHandControl_;
	PlayerControl *curPlayerControl_;
	Gtk::Box windowPanels_;
	Gtk::Box playersBox_;
	std::vector<PlayerControl *> playerControls_;
	TableControl tableControl_;
	ToolBarControl toolBarControl_;
};
