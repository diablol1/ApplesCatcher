
#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Apples Catcher"),
sceneManager(window.getSize())
{

}

void Game::start()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		processEvents();
		float deltaTime = clock.getElapsedTime().asSeconds();
		sceneManager.update(deltaTime);
		clock.restart();
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			break;
		}
	}
}

void Game::render()
{
	window.clear();

	window.draw(sceneManager);

	window.display();
}