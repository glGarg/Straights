#include "ToolBarControl.h"
#include "GuiView.h"

ToolBarControl::ToolBarControl(GuiView *view) : Gtk::Frame(), view_(view), seedEntry_(), startNewGame_("New Game With Seed"),
                                                endGame_("End Game")
{
    toolBarBox_.pack_start(startNewGame_);
    toolBarBox_.pack_start(seedEntry_);
    toolBarBox_.pack_start(endGame_);

    seedEntry_.set_text("0");

    endGame_.signal_clicked().connect(sigc::mem_fun(*this, &ToolBarControl::endGame));
    startNewGame_.signal_clicked().connect(sigc::mem_fun(*this, &ToolBarControl::startNewGame));

    add(toolBarBox_);
}

ToolBarControl::~ToolBarControl() {}

void ToolBarControl::startNewGame() const 
{
    const std::string inputSeed = seedEntry_.get_text();
    int seed = std::atoi(inputSeed.c_str());
    view_->restartGameWithSeed(seed);
}

void ToolBarControl::endGame() const
{
    view_->quitGame();
}
