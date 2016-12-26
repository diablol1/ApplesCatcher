#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <vector>

#include "Player.h"
#include "Apple.h"

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

	TextureManager textureManager;

	void loadTextures();
	void initWalls();
	
	void processEvents();
	void update(const float& deltaTime);
	void detectCollisions();
	bool isCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) const;
	void render();

	void reset();
};

