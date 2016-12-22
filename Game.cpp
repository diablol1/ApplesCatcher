#include "Game.h"


Game::Game() : window(sf::VideoMode(800, 600), "Apples Catcher")
{
	window.setFramerateLimit(60);
	loadTextures();
	player = Player(playerTexture);
}

void Game::start()
{
	while (window.isOpen())
	{
		processEvents();
		update();
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

void Game::update()
{

}
void Game::render()
{
	window.clear();

	window.draw(player);
	
	window.display();
}

void Game::loadTextures()
{
	if (!playerTexture.loadFromFile("sprites/tmpPlayer.png"))
		printf("Encountered error while loading texture.");
}
