#include "PlayerControl.h"
#include "GuiView.h"

PlayerControl::PlayerControl(GuiView *view, int index) : Gtk::Frame("Player " + std::to_string(index + 1)), playerBox_(Gtk::ORIENTATION_VERTICAL),
                                                         view_(view), rage_("Rage Quit!"), playerIndex_(index), discardCount_(0),
                                                         score_(0), info_("0 points\n0 discards"), playerRageQuit_(false)
{
    playerBox_.pack_start(rage_);
    playerBox_.pack_start(info_);

    rage_.signal_clicked().connect(sigc::mem_fun(*this, &PlayerControl::rageQuit));
    rage_.set_sensitive(false);

    add(playerBox_);
}

PlayerControl::~PlayerControl() {}

void PlayerControl::reset()
{
    discardCount_ = 0;
    playerRageQuit_ = false;
    rage_.set_sensitive(false);
    updateLabel();
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

void PlayerControl::setDiscardCount(int count)
{
    discardCount_ = count;
    updateLabel();
}

int PlayerControl::getDiscardCount() const { return discardCount_; }

void PlayerControl::setScore(int score)
{
    score_ = score;
    updateLabel();
}

void PlayerControl::updateLabel()
{
    info_.set_label(std::to_string(score_) + " points\n" + std::to_string(discardCount_) + " discards");
}

void PlayerControl::rageQuit()
{
    view_->playerRageQuit(playerIndex_);
    rage_.set_sensitive(false);
    playerRageQuit_ = true;
}
