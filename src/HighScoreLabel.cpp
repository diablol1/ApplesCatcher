#include "HighScoreLabel.h"

void HighScoreLabel::readFromFile(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (file.is_open())
	{
		std::stringstream ss;
		ss << file.rdbuf();
		file.close();

		score = std::stoi(ss.str());
		text.setString("HIGH SCORE: " + std::to_string(score));
	}
}

void HighScoreLabel::writeToFile(const std::string& fileName)
{
	std::ofstream file(fileName, std::ios::trunc);
	if (file.is_open())
	{
		file << score;
		file.close();
	}
}

void HighScoreLabel::setScore(int _score)
{
	score = _score;
	text.setString("HIGH SCORE: " + std::to_string(_score));
}