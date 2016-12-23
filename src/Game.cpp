#include "Game.h"

const sf::Vector2i Game::ScreenResolution = sf::Vector2i(800, 600);

Game::Game() : window(sf::VideoMode(ScreenResolution.x, ScreenResolution.y), "Apples Catcher")
{
	initWalls();

	loadTextures();
	player = Player(playerTexture, sf::Vector2f(ScreenResolution.x / 2,
		ScreenResolution.y - playerTexture.getSize().y - walls["bottomWall"].getSize().y));
}

void Game::loadTextures()
{
	if (!playerTexture.loadFromFile("sprites/tmpPlayer.png"))
		printf("Encountered error while loading texture.");
}

void Game::initWalls()
{
	walls["leftWall"].setSize(sf::Vector2f(30, ScreenResolution.y));
	walls["rightWall"].setSize(sf::Vector2f(30, ScreenResolution.y));
	walls["bottomWall"].setSize(sf::Vector2f(ScreenResolution.x, 30));

	walls["leftWall"].setPosition(0, 0);
	walls["rightWall"].setPosition(ScreenResolution.x - walls["rightWall"].getSize().x, 0);
	walls["bottomWall"].setPosition(0, ScreenResolution.y - walls["bottomWall"].getSize().y);

	for (auto &wall : walls)
	{
		wall.second.setFillColor(sf::Color::Magenta);
	}
}


void Game::start()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		processEvents();
		//TODO: Hmm, Maybe I should change this to miliseconds for better collison precision...
		float deltaTime = clock.getElapsedTime().asSeconds();
		update(deltaTime);
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

void Game::update(const float &deltaTime)
{
	player.move(deltaTime);
}
void Game::render()
{
	window.clear();

	window.draw(player);
	for (auto &wall : walls)
	{
		window.draw(wall.second);
	}
	
	window.display();
}