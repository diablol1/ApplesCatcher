#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <vector>

#include "Player.h"
#include "Apple.h"

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

	sf::Texture playerTexture;
	sf::Texture appleTexture;
	sf::Texture backgroundTexture;
	sf::Texture wallTexture;
	//TODO: Add texture manager

	void loadTextures();
	void initWalls();
	
	void processEvents();
	void update(const float& deltaTime);
	void detectCollisions();
	bool isCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) const;
	void render();

	void reset();
};

