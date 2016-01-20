#include "Game.h"

Game::Game()
{
	//create window which is size of desktop
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	window.create(sf::VideoMode(desktop.width, desktop.height, desktop.bitsPerPixel), "Roguelike");

	//create new level
	currentlevel = new Level(1);
	currentlevel->setLevel(Begin);

	//set initial deltatime as zero
	deltatime = 0;

	//set the view
	view.reset(sf::FloatRect(0,0, desktop.width, desktop.height));
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.5f, 1.5f));
}

void Game::start()
{
	//while window is open, keep running the gameloop
	//window.setFramerateLimit(20);
	while(window.isOpen())
	{
		gameloop();
	}
}

void Game::gameloop()
{
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

	window.clear();

	//poll window for events
	sf::Event evt;
	window.pollEvent(evt);
	
	//close window if window close button or esc key is clicked
	if(evt.type == sf::Event::Closed) window.close();
	if(evt.type == sf::Event::KeyPressed)
		if(evt.key.code == sf::Keyboard::Escape)
			window.close();

	if(currentlevel->currentleveltype == Dungeon) window.setView(view);

	//update and draw the current level to the screen
	currentlevel->update(deltatime, evt, view);
	currentlevel->draw(window);

	window.display();
	//calculate deltatime for one iteration of gameloop
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	deltatime = time_span.count()*1000;
	//std::cout<<1/deltatime<<std::endl;
}