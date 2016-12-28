#include "SceneManager.h"


SceneManager::SceneManager(const sf::Vector2u& _windowResolution) :
	currentScoreLabel("SCORE: 0", 30, sf::Vector2f(30, WindowResolution.y - 35)),
	highScoreLabel("HIGHSCORE: 0", 30, sf::Vector2f(WindowResolution.x - 215, WindowResolution.y - 35)),
	WindowResolution(_windowResolution)
{
	std::cout << WindowResolution.x << std::endl << WindowResolution.y << std::endl;
	loadTextures();
	background.setTexture(textureManager.get("background"));

	initWalls();
	reset();

	highScoreLabel.readFromFile("highscore.txt");
}

void SceneManager::initWalls()
{
	walls["leftWall"].setSize(sf::Vector2f(30, static_cast<float> (WindowResolution.y)));
	walls["rightWall"].setSize(sf::Vector2f(30, static_cast<float> (WindowResolution.y)));
	walls["bottomWall"].setSize(sf::Vector2f(static_cast<float> (WindowResolution.x), 30));

	walls["leftWall"].setPosition(0, 0);
	walls["rightWall"].setPosition(WindowResolution.x - walls["rightWall"].getSize().x, 0);
	walls["bottomWall"].setPosition(0, WindowResolution.y - walls["bottomWall"].getSize().y);

	for (auto &wall : walls)
	{
		wall.second.setTexture(&textureManager.get("wall"));
	}
}

void SceneManager::loadTextures()
{
	textureManager.add("player", "sprites/hat.png");
	textureManager.add("apple", "sprites/apple.png");
	textureManager.add("background", "sprites/background.png");
	textureManager.add("wall", "sprites/wall.jpg");
}

void SceneManager::update(const float &deltaTime)
{
	static sf::Clock clock;
	if (clock.getElapsedTime().asSeconds() >= 1)
	{
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

void SceneManager::detectCollisions()
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

	if (!apples.empty())
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

bool SceneManager::isCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) const
{
	if (rect1.intersects(rect2))
		return true;
	else
		return false;
}

sf::Vector2f SceneManager::generatePositionForApple()
{
	int positionX = generateNumber(walls["leftWall"].getSize().x,
		WindowResolution.x - walls["rightWall"].getSize().x - textureManager.get("apple").getSize().x);
	Apple tmpApple(textureManager.get("apple"), sf::Vector2f(positionX, 0), 0);

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

int SceneManager::generateNumber(const int& min, const int& max)
{
	static std::random_device rd;
	static std::mt19937 mt(rd());

	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

void SceneManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background);
	target.draw(player);
	for (const auto &wall : walls)
	{
		target.draw(wall.second);
	}
	for (const auto &apple : apples)
	{
		target.draw(apple);
	}
	target.draw(currentScoreLabel);
	target.draw(highScoreLabel);
}

void SceneManager::reset()
{
	if (apples.size() > 0)
		apples.clear();

	Apple::nextGravity = Apple::startingGravity;

	player = Player(textureManager.get("player"), sf::Vector2f(WindowResolution.x / 2,
		static_cast<float> (WindowResolution.y) - textureManager.get("player").getSize().y - walls["bottomWall"].getSize().y));

	currentScoreLabel.reset();
}