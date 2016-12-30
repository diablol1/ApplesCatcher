
#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Apples Catcher"),
	sceneManager(window.getSize()),
	menu(window.getSize(), &sceneManager.textureManager),
	gameState(gs::GameStates::MENU)
{}

void Game::start()
{
	sf::Clock clock;
	while (gameState != gs::GameStates::EXIT)
	{
		processEvents();
		if (gameState == gs::GameStates::PLAY)
		{
			float deltaTime = clock.getElapsedTime().asSeconds();
			sceneManager.update(deltaTime);
			clock.restart();
		}
		render();

	}
	window.close();
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
		else if (gameState == gs::GameStates::MENU && event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				menu.moveUp();
				break;

			case sf::Keyboard::Down:
				menu.moveDown();
				break;

			case sf::Keyboard::Return:
				switch (menu.getPressedOptionIndex())
				{
				case 0:
					gameState = gs::GameStates::PLAY;
					break;
				case 1:
					sceneManager.reset();
					gameState = gs::GameStates::PLAY;
					break;
				case 2:
					gameState = gs::GameStates::EXIT;
					break;
				}
				break;

			case sf::Keyboard::Escape:
				gameState = gs::GameStates::PLAY;
				break;
			}
			break;

		}
		else if (gameState == gs::GameStates::PLAY)
		{
			if (event.type == sf::Event::KeyReleased &&
				event.key.code == sf::Keyboard::Escape)
			{
				gameState = gs::GameStates::MENU;
			}
			else if (event.type == sf::Event::LostFocus)
				gameState = gs::GameStates::MENU;
		}
			
	}

}

void Game::render()
{
	window.clear();

	if (gameState == gs::GameStates::PLAY)
		window.draw(sceneManager);
	else
		window.draw(menu);

	window.display();
}