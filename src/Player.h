#pragma once
#include <SFML/Graphics.hpp>

#include "Enums.h"

class Player : public sf::Drawable, public sf::Transformable
{
public:

	cd::CollisionDirections collisionDirection;

	Player(const sf::Texture &texture, const sf::Vector2f &position);
	Player();
	Player& operator=(const Player& object);

	void move(const float& deltaTime);

	sf::FloatRect getGlobalBounds() const {
		return sprite.getGlobalBounds();
	}

private:
	const int moveSpeed;
	sf::Sprite sprite;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(sprite, states);
	}
};

