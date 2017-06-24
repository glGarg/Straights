#include "TextView.h"

TextView::TextView(GameController *controller, Game *game) : View(controller, game) {}

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

void TextView::update() const {}

bool TextView::isPlayerHuman() const
{
	char c;
	std::cin >> c;

	if (std::cin.fail())
	{
		std::cin.clear();
		return true;
	}
	else 
	{
		if (c == 'c')
		{
			return false;
		}

		return true;
	}
}
