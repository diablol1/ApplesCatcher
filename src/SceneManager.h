#pragma once

#include <SFML/Graphics.hpp>

#include <random>

#include "Player.h"
#include "TextureManager.h"
#include "Apple.h"
#include "CurrentScoreLabel.h"
#include "HighScoreLabel.h"

class SceneManager : public sf::Drawable
{
public:
	SceneManager(const sf::Vector2u& _windowResolution);

	void update(const float& deltaTime);
private:
	const sf::Vector2u WindowResolution;

	sf::Sprite background;

	Player player;
	std::vector<Apple>apples;
	std::map<std::string, sf::RectangleShape> walls;

	CurrentScoreLabel currentScoreLabel;
	HighScoreLabel highScoreLabel;

	TextureManager textureManager;

	void loadTextures();
	void initWalls();

	void detectCollisions();
	bool isCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) const;

	sf::Vector2f generatePositionForApple();
	int generateNumber(const int& min, const int& max);

	void reset();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};