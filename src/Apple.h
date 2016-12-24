#pragma once

#include <SFML/Graphics.hpp>

class Apple : public sf::Transformable, public sf::Drawable
{
public:
	Apple(const sf::Texture& texture, const sf::Vector2f& position);

private:
	sf::Sprite sprite;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(sprite, states);
	}
};

