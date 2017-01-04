#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Label : public sf::Drawable, public sf::Transformable
{
public:
	Label(const std::string& _text, const int& characterSize, const sf::Vector2f& position, const sf::Font& font);
	Label() {}
protected:
	sf::Text text;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};