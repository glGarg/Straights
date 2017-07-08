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

	app->run(view);

	return 0;
}