#include "TextView.h"

TextView::TextView(GameController *controller, Game *game) : View(controller, game) {}

TextView::~TextView() {}

void TextView::showMessage(std::string message) const
{
	std::cout << message << std::endl;
}

void TextView::showError(std::string error) const
{
	std::cout << error << std::endl;
}

void TextView::showPlayerPlay(int id, std::string card) const
{
	std::cout << "Player " << std::to_string(id) << " plays " << card + "." << std::endl;
}

void TextView::showPlayerDiscard(int id, std::string card) const
{
	std::cout << "Player " << std::to_string(id) << " discards " << card + "." << std::endl;
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

void TextView::showCardList(std::string label, std::vector<std::string>& cards) const
{
	std::string cardsIDs = label + ":";
	for (int i = 0; i < cards.size(); ++i)
	{
		cardsIDs += " " + cards[i];
	}

	std::cout << cardsIDs << std::endl;
}

bool TextView::isPlayerHuman() const
{
	char c;
	std::cout << ">";
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
