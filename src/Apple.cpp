#include "Apple.h"
#include <iostream>

const int Apple::startingGravity = 400;
int Apple::nextGravity = Apple::startingGravity;

Apple::Apple(const sf::Texture& texture, const sf::Vector2f& position)
{
	sprite.setTexture(texture);
	sprite.setPosition(position);
	
	nextGravity += 10;
	gravity = nextGravity;
	std::cout << gravity << std::endl;
}

Apple::Apple(const sf::Texture & texture, const sf::Vector2f & position, const int & _gravity)
{
	sprite.setTexture(texture);
	sprite.setPosition(position);
}

Apple & Apple::operator=(const Apple & object)
{
	if (this == &object)
		return *this;
	else
	{
		new (this) Apple(object);
		return *this;
	}
}
