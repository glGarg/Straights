#include "PlayerControl.h"
#include "GuiView.h"

PlayerControl::PlayerControl(GuiView *view, int index) : Gtk::Box(Gtk::ORIENTATION_VERTICAL), view_(view),
                                                         rage_("Rage Quit!"), playerIndex_(index), discardCount_(0),
                                                         score_(0), info_("0 points\n0 discards"),
                                                         playerId_("Player " + std::to_string(index))
{
    pack_start(playerId_);
    pack_start(rage_);
    pack_start(info_);
}

PlayerControl::~PlayerControl() {}

void PlayerControl::rageQuit() const
{
    view_->playerRageQuit(playerIndex_);
}
