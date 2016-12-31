#pragma once

#include "Label.h"

class CurrentScoreLabel : public Label
{
public:
	int score;

	CurrentScoreLabel
		(const std::string& _text,
		const unsigned int& characterSize,
		const sf::Vector2f& position) :
		Label(_text, characterSize, position)
	{}

	CurrentScoreLabel operator++(int);
	void reset();
};