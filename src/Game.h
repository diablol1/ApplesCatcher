#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <vector>
#include <random>

#include "Player.h"
#include "Apple.h"

#include "CurrentScoreLabel.h"
#include "HighScoreLabel.h"

#include "TextureManager.h"


class Game
{
public:
	Game();
	void start();

private:
	sf::RenderWindow window;

	sf::Sprite background;
	std::map<std::string, sf::RectangleShape> walls;
	std::vector<Apple>apples;
	Player player;

	CurrentScoreLabel currentScoreLabel;
	HighScoreLabel highScoreLabel;

	TextureManager textureManager;

	void loadTextures();
	void initWalls();
	
	void processEvents();
	void update(const float& deltaTime);
	void detectCollisions();
	bool isCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) const;
	void render();

	sf::Vector2f generatePositionForApple();
	int generateNumber(const int& min, const int& max);

	void reset();
};

