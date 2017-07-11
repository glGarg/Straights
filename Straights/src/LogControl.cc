#include "LogControl.h"
#include "GuiView.h"

LogControl::LogControl(GuiView *view) : view_(view), text_(""), buffer_(Gtk::TextBuffer::create())
{
    textView_.set_wrap_mode(Gtk::WrapMode::WRAP_WORD);
    textView_.set_buffer(buffer_);

    scrolledWindow_.add(textView_);
    scrolledWindow_.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    add(scrolledWindow_);
}

LogControl::~LogControl() {}

void LogControl::reset()
{
    text_ = "";
    updateTextView();
}

void LogControl::appendText(std::string log)
{
    text_ += "\n" + log;
    updateTextView();
}

void LogControl::updateTextView()
{
    buffer_->set_text(text_);
}
