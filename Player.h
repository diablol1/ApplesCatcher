#pragma once
#include <SFML/Graphics.hpp>

class Player : public sf::Drawable, public sf::Transformable
{
public:

	Player(const sf::Texture &texture, const sf::Vector2f &position);
	Player();
	Player& operator=(const Player& object)
	{
		if (this == &object)
			return *this;
		else
		{
			new (this) Player(object);
			return *this;
		}
	}

	void move(const float &deltaTime);

private:
	const int moveSpeed;
	sf::Sprite sprite;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(sprite, states);
	}
};

