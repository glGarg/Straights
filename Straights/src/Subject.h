#pragma once
#include <iostream>
#include <vector>
#include "Observer.h"

class Subject
{
public:
	Subject();
	virtual ~Subject();
	void subscribe(Observer *);
	void unsubscribe(Observer *);
protected:
	void notify();
private:
	std::vector<Observer *> observers_;
};

