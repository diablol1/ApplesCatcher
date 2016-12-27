#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Label : public sf::Drawable, public sf::Transformable
{
public:
	Label(const std::string& _text, const unsigned int& characterSize, const sf::Vector2f& position)
	{
		font.loadFromFile("font.ttf"); //This font contains only uppercase letters
		text = sf::Text(_text, font);
		text.setCharacterSize(characterSize);
		text.setPosition(position);
	}
protected:
	sf::Font font;
	sf::Text text;
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(text, states);
	}
};