#pragma once
#include "View.h"
#include "DeckGui.h"
#include "PlayerControl.h"
#include "HandControl.h"
#include "ToolBarControl.h"
#include "TableControl.h"
#include "LogControl.h"
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
	void reset() override;
	void showMessage(std::string) const override;
	void showError(std::string) const override;
	void showPlayerPlay(int, std::string) override;
	void showPlayerDiscard(int, std::string) const override;
	void printDeck(const std::vector<std::string>&) const override;
	void showCardList(std::string, std::vector<std::string>&) const override;
	void showWinners(std::vector<int>&) const override;
	bool isPlayerHuman() const override;
	void getUserInput() override;
	std::vector<std::string> getPlayerLegalPlays(int) const;
	std::vector<std::string> getPlayerHand(int) const;

	//Gameplay functions
	void playerRageQuit(int);
	void playerPlayedCard(std::string);
	void playerDiscardedCard(std::string);
	void quitGame();
	void restartGameWithSeed(int);
	void updateDisplay() override;
	void updateScore(std::vector<int>&) override;
private:
	GameController *controller_;
	Game *game_;
	DeckGui *deckGui_;
	HandControl *curHandControl_;
	PlayerControl *curPlayerControl_;
	Gtk::Box handBox_;
	Gtk::Box windowBox_;
	Gtk::Box gameBox_;
	Gtk::Box logBox_;
	Gtk::Box playersBox_;
	LogControl logControl_;
	TableControl tableControl_;
	ToolBarControl toolBarControl_;
	std::vector<HandControl *> handControls_;
	std::vector<PlayerControl *> playerControls_;
};
