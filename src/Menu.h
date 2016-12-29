#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "Label.h"
#include "TextureManager.h"

class Menu : public sf::Drawable
{
public:
	Menu(const sf::Vector2u& _windowResolution, TextureManager* _textureManager);

	void moveUp();
	void moveDown();
	int getPressedOptionIndex();
private:
	static const int numberOfOptions;
	int selectedOptionIndex;
	sf::Font font;
	sf::Text options[3];
	sf::Text author;

	sf::Sprite background;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};