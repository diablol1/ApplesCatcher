#include "Game.h"

const sf::Vector2i Game::ScreenResolution = sf::Vector2i(800, 600);

Game::Game() : window(sf::VideoMode(ScreenResolution.x, ScreenResolution.y), "Apples Catcher")
{
	window.setFramerateLimit(60);
	loadTextures();
	player = Player(playerTexture, sf::Vector2f(ScreenResolution.x / 2, ScreenResolution.y - playerTexture.getSize().y));
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
