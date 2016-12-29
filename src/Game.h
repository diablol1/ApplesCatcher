#pragma once

#include "SceneManager.h"
#include "Menu.h"
#include "Enums.h"

class Game
{
public:
	Game();
	void start();

private:
	gs::GameStates gameState;

	sf::RenderWindow window;

	SceneManager sceneManager;
	Menu menu;
	
	void processEvents();
	void render();
};

