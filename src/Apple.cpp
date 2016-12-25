#include "Apple.h"


Apple::Apple(const sf::Texture& texture, const sf::Vector2f& position, const int& _gravity) : gravity(_gravity)
{
	sprite.setTexture(texture);
	sprite.setPosition(position);
}