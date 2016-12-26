#pragma once

#include <SFML/Graphics.hpp>

class Apple : public sf::Transformable, public sf::Drawable
{
public:
	Apple(const sf::Texture& texture, const sf::Vector2f& position, const int& _gravity = 250);

	void move(const float& deltaTime) {
		sprite.move(0, gravity * deltaTime);
	}

	sf::FloatRect getGlobalBounds() const {
		return sprite.getGlobalBounds();
	}
private:
	sf::Sprite sprite;
	const int gravity;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(sprite, states);
	}
};

