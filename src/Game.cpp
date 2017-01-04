
#include "Game.h"

const sf::Time Game::splashScreenDisplayTime(sf::Time(sf::seconds(1)));

Game::Game() :
	window(sf::VideoMode(800, 600), "Apples Catcher"),
	sceneManager(window.getSize(), &gameState, &textureCache, &soundCache),
	menu(window.getSize(), &textureCache),
	gameState(gs::GameStates::SPLASH_SCREEN)
{
	splashScreenSprite.setTexture(textureCache.get("splashScreen"));
	music.openFromFile("data/music.ogg");
	music.setVolume(65);
	music.setLoop(true);
	music.play();
}

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
		else if (gameState == gs::GameStates::SPLASH_SCREEN)
		{
			static sf::Clock ssDisplayingClock;
			if (ssDisplayingClock.getElapsedTime() >= splashScreenDisplayTime)
			{
				ssDisplayingClock.restart();
				gameState = gs::GameStates::MENU;
			}
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
			gameState = gs::GameStates::EXIT;
			break;
		}
		else if (gameState == gs::GameStates::MENU && event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				soundCache.play("menuMove");
				menu.moveUp();
				break;

			case sf::Keyboard::Down:
				soundCache.play("menuMove");
				menu.moveDown();
				break;

			case sf::Keyboard::Return:
				soundCache.play("menuSelect");
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
					if (music.getStatus() == sf::Music::Status::Playing)
					{
						music.stop();
						menu.setStringForOption(2, "MUSIC: OFF");
					}
					else
					{
						music.play();
						menu.setStringForOption(2, "MUSIC: ON");
					}
					break;
				case 3:
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
	else if (gameState == gs::GameStates::MENU)
		window.draw(menu);
	else
		window.draw(splashScreenSprite);
	window.display();
}