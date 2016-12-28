#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "Apples Catcher"),
	currentScoreLabel("SCORE: 0", 30, sf::Vector2f(30, window.getSize().y - 35)),
	highScoreLabel("HIGHSCORE: 0", 30, sf::Vector2f(window.getSize().x - 215, window.getSize().y - 35))
{
	loadTextures();
	background.setTexture(textureManager.get("background"));

	initWalls();
	reset();

	apples.push_back(Apple(textureManager.get("apple"), sf::Vector2f(90, 90)));
	highScoreLabel.readFromFile("highscore.txt");
}

void Game::loadTextures()
{
	textureManager.add("player", "sprites/hat.png");
	textureManager.add("apple", "sprites/apple.png");
	textureManager.add("background", "sprites/background.png");
	textureManager.add("wall", "sprites/wall.jpg");
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
		wall.second.setTexture (&textureManager.get ("wall"));
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
	static sf::Clock clock;
	if (clock.getElapsedTime().asSeconds() >= 1)
	{
		if (!apples.empty())
		{
			int lastAppleGravity = apples[apples.size() - 1].gravity;
			int nextAppleGravity;
				nextAppleGravity = lastAppleGravity + 5;

			apples.push_back(Apple(textureManager.get("apple"), generatePositionForApple(), nextAppleGravity));
		}
		else
			apples.push_back(Apple(textureManager.get("apple"), generatePositionForApple()));

		clock.restart();
	}

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

	if(!apples.empty())
	{
		Apple oldestApple = apples[0];
		if (isCollision(walls["bottomWall"].getGlobalBounds(), oldestApple.getGlobalBounds())) //Check game over
		{
			if (currentScoreLabel.score > highScoreLabel.score)
			{
				highScoreLabel.setScore(currentScoreLabel.score);
				highScoreLabel.writeToFile("highscore.txt");
			}
			reset();
		}
		else if (isCollision(player.getGlobalBounds(), oldestApple.getGlobalBounds()))
		{
			apples.erase(apples.begin());
			currentScoreLabel++;
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

	window.draw(background);
	window.draw(player);
	for (const auto &wall : walls)
	{
		window.draw(wall.second);
	}
	for (const auto &apple : apples)
	{
		window.draw(apple);
	}
	window.draw(currentScoreLabel);
	window.draw(highScoreLabel);
	
	window.display();
}

sf::Vector2f Game::generatePositionForApple()
{
	int positionX = generateNumber (walls["leftWall"].getSize().x,
		window.getSize().x - walls["rightWall"].getSize().x - textureManager.get("apple").getSize().x);
	Apple tmpApple(textureManager.get("apple"), sf::Vector2f(positionX, 0));
	
	for (const auto& apple : apples)
	{
		if (isCollision(tmpApple.getGlobalBounds(), apple.getGlobalBounds()))
		{
			generatePositionForApple();
			break;
		}
	}
	return sf::Vector2f(positionX, 0);
}

int Game::generateNumber(const int& min, const int& max)
{
	static std::random_device rd;
	static std::mt19937 mt(rd());

	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}



void Game::reset()
{
	if(apples.size() > 0)
		apples.clear();

	player = Player (textureManager.get ("player"), sf::Vector2f (window.getSize().x / 2,
		static_cast<float> (window.getSize().y) - textureManager.get ("player").getSize().y - walls["bottomWall"].getSize().y));

	currentScoreLabel.reset();
}
