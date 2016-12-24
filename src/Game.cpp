#include "Game.h"

const sf::Vector2i Game::ScreenResolution = sf::Vector2i(1200, 800);

Game::Game() : window(sf::VideoMode(ScreenResolution.x, ScreenResolution.y), "Apples Catcher")
{
	initWalls();

	loadTextures();
	player = Player(playerTexture, sf::Vector2f(ScreenResolution.x / 2,
		static_cast<float>(ScreenResolution.y) - playerTexture.getSize().y - walls["bottomWall"].getSize().y));

	apples.push_back(Apple(appleTexture, sf::Vector2f(90, 90)));
}

void Game::loadTextures()
{
	playerTexture.loadFromFile("sprites/tmpPlayer.png");
	appleTexture.loadFromFile("sprites/tmpApple.png");
}

void Game::initWalls()
{
	walls["leftWall"].setSize(sf::Vector2f(30, static_cast<float>(ScreenResolution.y)));
	walls["rightWall"].setSize(sf::Vector2f(30, static_cast<float>(ScreenResolution.y)));
	walls["bottomWall"].setSize(sf::Vector2f(static_cast<float>(ScreenResolution.x), 30));

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
}

bool Game::isCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
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
	for (auto &wall : walls)
	{
		window.draw(wall.second);
	}
	for (auto &apple : apples)
	{
		window.draw(apple);
	}
	
	window.display();
}

sf::Vector2f Game::drawApplePosition()
{
	//Resursion if(position collide It call again and again... if it doesn't collide it return what it should hmm )
	return sf::Vector2f();
}
