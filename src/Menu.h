#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <array>

#include "Label.h"
#include "TextureCache.h"

class Menu : public sf::Drawable
{
public:
	Menu(const sf::Vector2u& _windowResolution, TextureCache* _textureManager);

	void moveUp();
	void moveDown();
	int getPressedOptionIndex() {
		return selectedOptionIndex;
	}
	void setStringForOption(const int & optionIndex, const std::string & text) {
		options[optionIndex].setString(text);
	}
private:
	static const int numberOfOptions;
	int selectedOptionIndex;
	sf::Font font;
	std::array<sf::Text, 4> options;
	sf::Text author;

	sf::Sprite background;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};