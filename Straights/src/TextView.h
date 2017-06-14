#pragma once
#include "View.h"

class TextView : public View
{
public:
	TextView();
	virtual ~TextView();
	void displayError(std::string) const override;
	void printDeck(const std::vector<std::string>&) const override;
};
