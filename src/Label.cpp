#include "Label.h"

Label::Label(const std::string& _text, const unsigned int& characterSize, const sf::Vector2f& position)
{
	font.loadFromFile("font.ttf"); //This font contains only uppercase letters
	text = sf::Text(_text, font);
	text.setCharacterSize(characterSize);
	text.setPosition(position);
}