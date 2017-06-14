#pragma once
#include "Command.h"

class Observer
{
public:
	Observer();
	virtual ~Observer();
	virtual bool notify(Command&) = 0;
};
