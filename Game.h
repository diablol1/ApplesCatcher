#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"

class Game
{
public:
	Game();
	void start();

private:
	static const sf::Vector2i ScreenResolution;
	sf::RenderWindow window;

	Player player;
	sf::Texture playerTexture;

	void loadTextures();

	void processEvents();
	void update(const float &deltaTime);
	void render();
};

