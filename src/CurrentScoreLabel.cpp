#include "CurrentScoreLabel.h"

CurrentScoreLabel CurrentScoreLabel::operator++(int)
{
	CurrentScoreLabel copy(*this);
	score++;
	text.setString("SCORE: " + std::to_string(score));
	return copy;
}

void CurrentScoreLabel::reset()
{
	score = 0;
	text.setString("SCORE: " + std::to_string(score));
}