#pragma once

#include <SFML/Graphics.hpp>
#include "SceneManager.h"

class Game
{
public:
	Game();
	void start();

private:
	sf::RenderWindow window;

	SceneManager sceneManager;
	
	void processEvents();
	void render();
};

