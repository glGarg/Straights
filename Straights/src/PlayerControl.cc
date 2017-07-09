#include "PlayerControl.h"
#include "GuiView.h"

PlayerControl::PlayerControl(GuiView *view, int index) : Gtk::Box(Gtk::ORIENTATION_VERTICAL), view_(view),
                                                         rage_("Rage Quit!"), playerIndex_(index), discardCount_(0),
                                                         score_(0), info_("0 points\n0 discards"), playerRageQuit_(false),
                                                         playerId_("Player " + std::to_string(index + 1))
{
    pack_start(playerId_);
    pack_start(rage_);
    pack_start(info_);

    rage_.signal_clicked().connect(sigc::mem_fun(*this, &PlayerControl::rageQuit));
    rage_.set_sensitive(false);
}

bool PlayerControl::getRageQuit() const
{
    return playerRageQuit_;
}

void PlayerControl::enableRage()
{
    rage_.set_sensitive(true);
}

void PlayerControl::disableRage()
{
    rage_.set_sensitive(false);
}

PlayerControl::~PlayerControl() {}

void PlayerControl::setDiscardCount(int count)
{
    discardCount_ = count;
    info_.set_label(std::to_string(score_) + " points\n" + std::to_string(discardCount_) + " discards");
}

int PlayerControl::getDiscardCount() const { return discardCount_; }

void PlayerControl::rageQuit()
{
    view_->playerRageQuit(playerIndex_);
    rage_.set_sensitive(false);
    playerRageQuit_ = true;
}
