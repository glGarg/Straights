#include "Subject.h"

Subject::Subject() {}

Subject::~Subject() {}

void Subject::subscribe(View *o)
{
	observers_.push_back(o);
}

void Subject::unsubscribe(View *o) {}

void Subject::notify(std::string notification) const
{
	for (auto &o : observers_)
	{
		o->displayMessage(notification);
	}
}

void Subject::notify(std::vector<std::string>& info) const
{
	for (auto &o : observers_)
	{
		o->printDeck(info);
	}
}

bool Subject::isPlayerHuman(int id) const
{
	if (observers_.size() > 0) 
	{
		notify("Is player " + std::to_string(id) + " a human(h) or a computer(c)?");
		return observers_[0]->isPlayerHuman();
	}

	return true;
}
