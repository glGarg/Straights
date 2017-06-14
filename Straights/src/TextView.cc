#include "TextView.h"

TextView::TextView() {}

TextView::~TextView() {}

void TextView::displayError(std::string error) const
{
	std::cout << error << std::endl;
}

void TextView::printDeck(const std::vector<std::string>& cards) const
{
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 13; ++j)
		{
			if (j != 0)
			{
				std::cout << " ";
			}
			std::cout << cards[13 * i + j];
		}
		std::cout << std::endl;
	}
}