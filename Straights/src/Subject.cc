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
