#pragma once

#include "SceneManager.h"
#include "SoundCache.h"
#include "Menu.h"
#include "Enums.h"

#include <SFML/Audio.hpp>

class Game
{
public:
	Game();
	void start();

private:
	static const sf::Time splashScreenDisplayTime;

	TextureCache textureCache;
	SoundCache soundCache;
	sf::Music music;

	gs::GameStates gameState;
	sf::RenderWindow window;

	sf::Sprite splashScreenSprite;
	SceneManager sceneManager;
	Menu menu;
	
	void processEvents();
	void render();
};

