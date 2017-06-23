#include "Subject.h"

Subject::Subject() {}

Subject::~Subject() {}

void Subject::subscribe(Observer *o)
{
	observers_.push_back(o);
}

void Subject::unsubscribe(Observer *o) {}

void Subject::notify()
{
	for (auto &o : observers_)
	{
		o->update();
	}
}
