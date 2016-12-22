#include "Player.h"

Player::Player(const sf::Texture &texture, const sf::Vector2f &position)
{
	sprite.setTexture(texture);
	sprite.setPosition(position);
}