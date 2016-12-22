#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"

class Game
{
public:

	sf::RenderWindow window;

	Game();
	void start();

	void processEvents();
	void update();
	void render();
private:
	Player player;
	sf::Texture playerTexture;

	void loadTextures();
};

