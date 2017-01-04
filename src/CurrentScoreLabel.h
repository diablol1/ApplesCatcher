#pragma once

#include "Label.h"

class CurrentScoreLabel : public Label
{
public:
	int score;

	CurrentScoreLabel
		(const std::string& _text,
		const int& characterSize,
		const sf::Vector2f& position,
		const sf::Font& font) :
			Label(_text, characterSize, position, font)
	{}

	CurrentScoreLabel operator++(int);
	void reset();
};