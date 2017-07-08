#include "ToolBarControl.h"
#include "GuiView.h"

ToolBarControl::ToolBarControl(GuiView *view) : view_(view), seedEntry_(), startNewGame_("New Game With Seed"),
                                                endGame_("End Game")
{
    pack_start(startNewGame_);
    pack_start(seedEntry_);
    pack_start(endGame_);

    seedEntry_.set_text("0");
}

ToolBarControl::~ToolBarControl() {}

void ToolBarControl::startNewGame() const {}

void ToolBarControl::endGame() const {}
