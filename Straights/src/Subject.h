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
	void notify(std::string) const;
	void notify(std::vector<std::string>&) const;
	bool isPlayerHuman(int) const;
private:
	std::vector<View *> observers_;
};

