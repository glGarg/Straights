#pragma once
#include <iostream>
#include <vector>
#include "View.h"

class Subject
{
public:
	Subject();
	virtual ~Subject();
	void subscribe(View *);
	void unsubscribe(View *);
protected:
	void notify();
private:
	std::vector<View *> observers_;
};

