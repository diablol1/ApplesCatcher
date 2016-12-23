#include "Player.h"

Player::Player() : moveSpeed(600) {}


Player::Player(const sf::Texture &texture, const sf::Vector2f &position): Player()
{
	sprite.setTexture(texture);
	sprite.setPosition(position);
}

void Player::move(const float &deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		sprite.move(-moveSpeed * deltaTime, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		sprite.move(moveSpeed * deltaTime, 0);
}
