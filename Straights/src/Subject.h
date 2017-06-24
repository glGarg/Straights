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
	bool isPlayerHuman() const;
private:
	std::vector<View *> observers_;
};

