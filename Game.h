#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"

class Game
{
public:
	Game();
	void start();

private:
	sf::RenderWindow window;

	Player player;
	sf::Texture playerTexture;

	void loadTextures();

	void processEvents();
	void update();
	void render();
};

