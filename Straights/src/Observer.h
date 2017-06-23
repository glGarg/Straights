#pragma once

class Observer
{
public:
	Observer();
	virtual ~Observer();
	virtual void update() const = 0;
};
