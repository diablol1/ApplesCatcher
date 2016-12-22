#include "Player.h"

sf::Texture Player::texture = sf::Texture();

Player::Player(const sf::Texture &texture)
{
	sprite.setTexture(texture);
}