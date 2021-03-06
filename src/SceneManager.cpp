#include "SceneManager.h"


SceneManager::SceneManager(
	const sf::Vector2u& _windowResolution,
	gs::GameStates* _gameState,
	TextureCache* _textureCache,
	SoundCache* _soundCache,
	const sf::Font &font) :

	currentScoreLabel("SCORE: 0", 30, sf::Vector2f(30, WindowResolution.y - 35), font),
	highScoreLabel("HIGHSCORE: 0", 30, sf::Vector2f(WindowResolution.x - 215, WindowResolution.y - 35), font),
	WindowResolution(_windowResolution),
	gameState(_gameState),
	textureCache(_textureCache),
	soundCache(_soundCache)
{
	background.setTexture(textureCache->get("background"));

	initWalls();
	reset();

	highScoreLabel.readFromFile("data/highscore");
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
		wall.second.setTexture(&textureCache->get("wall"));
	}
}

void SceneManager::update(const float &deltaTime)
{
	static sf::Clock clock;
	if (clock.getElapsedTime().asSeconds() >= 1)
	{
		apples.push_back(Apple(textureCache->get("apple"), generatePositionForApple()));
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
		for (const auto& apple : apples)
		{
			if (isCollision(walls["bottomWall"].getGlobalBounds(), apple.getGlobalBounds())) //Check game over
			{
				soundCache->play("fail");
				if (currentScoreLabel.score > highScoreLabel.score)
				{
					highScoreLabel.setScore(currentScoreLabel.score);
					highScoreLabel.writeToFile("data/highscore");
				}
				*gameState = gs::GameStates::MENU;
				reset();
				break;
			}
		}
		
		for (std::list<Apple>::iterator it = apples.begin(); it != apples.end(); it++)
		{
			if (isCollision(it->getGlobalBounds(), player.getGlobalBounds()))
			{
				apples.erase(it);
				currentScoreLabel++;
				soundCache->play("appleCatch");
				break;
			}
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
		WindowResolution.x - walls["rightWall"].getSize().x - textureCache->get("apple").getSize().x);
	Apple tmpApple(textureCache->get("apple"), sf::Vector2f(positionX, textureCache->get("apple").getSize().y), 0);

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

	player = Player(textureCache->get("player"), sf::Vector2f(WindowResolution.x / 2,
		static_cast<float> (WindowResolution.y) - textureCache->get("player").getSize().y - walls["bottomWall"].getSize().y));

	currentScoreLabel.reset();
}