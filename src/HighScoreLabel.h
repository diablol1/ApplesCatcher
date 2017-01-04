#pragma once

#include <fstream>
#include <sstream>
#include <iostream>

#include "Label.h"

class HighScoreLabel : public Label
{
public:
	int score;

	HighScoreLabel
		(const std::string& _text,
		const int& characterSize,
		const sf::Vector2f& position,
		const sf::Font& font) :
			Label(_text, characterSize, position, font)
	{}

	void readFromFile(const std::string& fileName);
	void writeToFile(const std::string& fileName);

	void setScore(int _score);
};