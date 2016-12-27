#pragma once

#include "Label.h"

class CurrentScoreLabel : public Label
{
public:
	CurrentScoreLabel(const std::string& _text, const unsigned int& characterSize, const sf::Vector2f& position)
		: Label(_text, characterSize, position)
	{}

	CurrentScoreLabel operator++(int)
	{
		CurrentScoreLabel copy(*this);
		score++;
		text.setString("SCORE: " + std::to_string(score));
		return copy;
	}
	void reset() {
		score = 0;
		text.setString("SCORE: " + std::to_string(score));
	}
private:
	int score;
};