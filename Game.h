#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:

	sf::RenderWindow window;

	Game();
	void start();

	void processEvents();
	void update();
	void render();
};

