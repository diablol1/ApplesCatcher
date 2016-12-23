#include "Player.h"

Player::Player() : moveSpeed(600), collisionDirection(cd::CollisionDirections::ANY) {}

Player & Player::operator=(const Player & object)
{
	if (this == &object)
		return *this;
	else
	{
		new (this) Player(object);
		return *this;
	}
}


Player::Player(const sf::Texture &texture, const sf::Vector2f &position): Player()
{
	sprite.setTexture(texture);
	sprite.setPosition(position);
}

void Player::move(const float &deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && collisionDirection != cd::CollisionDirections::LEFT)
		sprite.move(-moveSpeed * deltaTime, 0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && collisionDirection != cd::CollisionDirections::RIGHT)
		sprite.move(moveSpeed * deltaTime, 0);
}
