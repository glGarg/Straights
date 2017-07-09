#include <iostream>
#include "Game.h"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		seed = std::stoi(argv[1]);
	}

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "Straights");

	Game game;
	GameController controller(&game);
	GuiView view(&controller, &game);
	view.init();

	try
	{
		app->run(view);
	}
	catch(Game::GameException &e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}