#include <iostream>
#include "Straights.h"

int main(int argc, char **argv)
{
	Straights& s = Straights::Instance();
	if (argc > 1)
	{
		seed = static_cast<int>(*argv[1]);
	}

	s.run();
	return 0;
}