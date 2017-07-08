#include "Subject.h"

Subject::Subject() {}

Subject::~Subject() {}

void Subject::subscribe(View *o)
{
	observers_.push_back(o);
}

void Subject::unsubscribe(View *o) {}

void Subject::showMessage(std::string message) const
{
	for (auto &o : observers_)
	{
		o->showMessage(message);
	}
}

void Subject::showError(std::string error) const
{
	for (auto &o : observers_)
	{
		o->showError(error);
	}
}

void Subject::showPlayerPlay(int id, std::string card) const
{
	for (auto &o : observers_)
	{
		o->showPlayerPlay(id, card);
	}
}

void Subject::showPlayerDiscard(int id, std::string card) const
{
	for (auto &o : observers_)
	{
		o->showPlayerDiscard(id, card);
	}
}

void Subject::printCards(std::vector<std::string>& deck) const
{
	for (auto &o : observers_)
	{
		o->printDeck(deck);
	}
}

void Subject::updateDisplay() const
{
	for (auto &o : observers_)
	{
		o->updateDisplay();
	}
}

bool Subject::isPlayerHuman(int id) const
{
	if (observers_.size() > 0) 
	{
		showMessage("Is player " + std::to_string(id) + " a human(h) or a computer(c)?");
		return observers_[0]->isPlayerHuman();
	}

	return true;
}

void Subject::showCardList(std::string label, std::vector<std::string>& cards) const
{
	for (auto &o : observers_)
	{
		o->showCardList(label, cards);
	}
}
