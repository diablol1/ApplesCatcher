#pragma once

#include <SFML/Graphics.hpp>

#include <random>
#include <list>

#include "Player.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Apple.h"
#include "CurrentScoreLabel.h"
#include "HighScoreLabel.h"

class SceneManager : public sf::Drawable
{
public:
	TextureManager* textureManager;
	SoundManager* soundManager;
	gs::GameStates* gameState;

	SceneManager(const sf::Vector2u& _windowResolution,
		gs::GameStates* _gameState,
		TextureManager* _textureManager,
		SoundManager* _soundManager);

	void update(const float& deltaTime);
	void reset();
private:
	const sf::Vector2u WindowResolution;

	sf::Sprite background;

	Player player;
	std::list<Apple>apples;
	std::map<std::string, sf::RectangleShape> walls;

	CurrentScoreLabel currentScoreLabel;
	HighScoreLabel highScoreLabel;

	sf::SoundBuffer catchSoundEffectBuffer;
	sf::Sound catchSoundEffect;

	void initWalls();

	void detectCollisions();
	bool isCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) const;

	sf::Vector2f generatePositionForApple();
	int generateNumber(const int& min, const int& max);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};