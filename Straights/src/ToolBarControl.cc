#include "ToolBarControl.h"
#include "GuiView.h"

ToolBarControl::ToolBarControl(GuiView *view) : view_(view), seedEntry_(), startNewGame_("New Game With Seed"),
                                                endGame_("End Game")
{
    pack_start(startNewGame_);
    pack_start(seedEntry_);
    pack_start(endGame_);

    seedEntry_.set_text("0");

    endGame_.signal_clicked().connect(sigc::mem_fun(*this, &ToolBarControl::endGame));
    startNewGame_.signal_clicked().connect(sigc::mem_fun(*this, &ToolBarControl::startNewGame));
}

ToolBarControl::~ToolBarControl() {}

void ToolBarControl::startNewGame() const 
{
    std::string inputSeed = seedEntry_->get_text();
    int seed = std::atoi(inputSeed);
    if (seed)
    {
        // start new game with seed
    }
    else
    {
        // start new game with 0
    }
}

void ToolBarControl::endGame() const
{
    view_->quitGame();
}
