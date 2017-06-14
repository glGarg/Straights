#include "View.h"

View::View() {}

View::~View() {}

void View::getUserInput()
{
	while (true)
	{
		Command c;
		std::cin >> c;
		if (std::cin.fail())
		{
			break;
		}
		for (auto &o : observers_)
		{
			if (o->notify(c) == false)
			{
				return;
			}
		}
	}
}

void View::attach(Observer *observer)
{
	observers_.push_back(observer);
}