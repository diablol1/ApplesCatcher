#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "Label.h"

class HighScoreLabel : public Label
{
public:
	int score;

	HighScoreLabel(const std::string& _text, const unsigned int& characterSize, const sf::Vector2f& position)
		: Label(_text, characterSize, position)
	{}

	void readFromFile(const std::string& fileName);
	void writeToFile(const std::string& fileName);

	void setScore(int _score);
};