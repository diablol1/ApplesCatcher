#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(1280, 800), "Apples Catcher")
{
	loadTextures();

	initWalls();
	reset();

	apples.push_back(Apple(appleTexture, sf::Vector2f(90, 90)));
}

void Game::loadTextures()
{
	playerTexture.loadFromFile("sprites/tmpPlayer.png");
	appleTexture.loadFromFile("sprites/tmpApple.png");
}

void Game::initWalls()
{
	walls["leftWall"].setSize(sf::Vector2f(30, static_cast<float> (window.getSize().y)));
	walls["rightWall"].setSize(sf::Vector2f(30, static_cast<float> (window.getSize().y)));
	walls["bottomWall"].setSize(sf::Vector2f(static_cast<float> (window.getSize().x), 30));

	walls["leftWall"].setPosition(0, 0);
	walls["rightWall"].setPosition(window.getSize().x - walls["rightWall"].getSize().x, 0);
	walls["bottomWall"].setPosition(0, window.getSize().y - walls["bottomWall"].getSize().y);

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
	for (auto &apple : apples)
	{
		apple.move(deltaTime);
	}
	detectCollisions();
}

void Game::detectCollisions()
{
	if (isCollision(player.getGlobalBounds(), walls["leftWall"].getGlobalBounds()))
	{
		player.collisionDirection = cd::CollisionDirections::LEFT;
	}
	else if (isCollision(player.getGlobalBounds(), walls["rightWall"].getGlobalBounds()))
	{
		player.collisionDirection = cd::CollisionDirections::RIGHT;
	}
	else
		player.collisionDirection = cd::CollisionDirections::ANY;

	for (auto const& apple : apples)
	{
		if (isCollision (walls["bottomWall"].getGlobalBounds(), apple.getGlobalBounds ())) //Check game over
		{
			reset();
			break;
		}
	}
}

bool Game::isCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) const
{
	if (rect1.intersects(rect2))
		return true;
	else
		return false;
}

void Game::render()
{
	window.clear();

	window.draw(player);
	for (const auto &wall : walls)
	{
		window.draw(wall.second);
	}
	for (const auto &apple : apples)
	{
		window.draw(apple);
	}
	
	window.display();
}

void Game::reset()
{
	if(apples.size() > 0)
		apples.clear();

	player = Player(playerTexture, sf::Vector2f(window.getSize().x / 2,
		static_cast<float>(window.getSize().y) - playerTexture.getSize().y - walls["bottomWall"].getSize().y));
}
