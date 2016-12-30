#pragma once

#include "SceneManager.h"
#include "SoundManager.h"
#include "Menu.h"
#include "Enums.h"

#include <SFML/Audio.hpp>

class Game
{
public:
	Game();
	void start();

private:
	SoundManager soundManager;
	sf::Music music;

	gs::GameStates gameState;
	sf::RenderWindow window;

	SceneManager sceneManager;
	Menu menu;
	
	void processEvents();
	void render();
};

