#include "Game.h"



Game::Game() : window(sf::VideoMode(800, 600), "Apples Catcher")
{
	window.setFramerateLimit(60);
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

}
void Game::update()
{

}
void Game::render()
{
	window.clear();
	//window.draw(object);
	window.display();
}