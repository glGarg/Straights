#include "Subject.h"

Subject::Subject() {}

Subject::~Subject() {}

void Subject::subscribe(View *o)
{
	observers_.push_back(o);
}

void Subject::unsubscribe(View *o) {}

void Subject::notify()
{
	for (auto &o : observers_)
	{
		o->update();
	}
}

bool Subject::isPlayerHuman() const
{
	if (observers_.size() > 0) 
	{
		return observers_[0]->isPlayerHuman();
	}

	return true;
}
