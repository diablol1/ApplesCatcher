#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "Player.h"

class Game
{
public:
	Game();
	void start();

private:
	static const sf::Vector2i ScreenResolution;
	sf::RenderWindow window;

	std::map<std::string, sf::RectangleShape> walls;
	Player player;
	sf::Texture playerTexture;

	void loadTextures();
	void initWalls();
	
	void processEvents();
	void update(const float &deltaTime);
	void render();
};

