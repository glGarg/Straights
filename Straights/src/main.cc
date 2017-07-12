#include <iostream>
#include "Game.h"
#include "Music.h"
#include <gst/gst.h>

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

	std::string filename = "../assets/music/Lepidoptera.ogg";
	const char *track = filename.c_str();
	if (argc > 2)
	{
		track = argv[2];
	}
	
	gst_init(&argc, &argv);
	Music music(track);
	music.play();

	try
	{
		app->run(view);
	}
	catch(Game::GameException &e)
	{
		std::cout << e.what() << std::endl;
	}

	music.stopPlaying();

	return 0;
}