#include "Label.h"

Label::Label(const std::string& _text, const int& characterSize, const sf::Vector2f& position, const sf::Font& font)
{
	text = sf::Text(_text, font);
	text.setCharacterSize(characterSize);
	text.setPosition(position);
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(text, states);
}