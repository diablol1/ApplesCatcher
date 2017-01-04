#include "Menu.h"


Menu::Menu(const sf::Vector2u & _windowResolution, TextureCache* _textureCache, const sf::Font& font)
{

	for (int i = 0; i < options.size(); i++)
	{
		options[i].setFont(font);
		options[i].setFillColor(sf::Color::White);
		options[i].setPosition(_windowResolution.x / 2 - 70, _windowResolution.y / 2 + i * 100 - 175);
		options[i].setCharacterSize(50);
	}
	options[0].setFillColor(sf::Color::Yellow);

	options[0].setString("PLAY");
	options[1].setString("RESET");
	options[2].setString("MUSIC: ON");
	options[3].setString("EXIT");

	selectedOptionIndex = 0;

	background.setTexture(_textureCache->get("background"));

	author = sf::Text("AUTHOR: PATRYK \"DIABLOL\" KRAJEWSKI", font, 20);
	author.setPosition(_windowResolution.x - 360, _windowResolution.y - 30);
}

void Menu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background);
	target.draw(author);
	for (int i = 0; i < options.size(); i++)
	{
		target.draw(options[i]);
	}
}

void Menu::moveUp()
{
	if (selectedOptionIndex - 1 >= 0)
	{
		options[selectedOptionIndex].setFillColor(sf::Color::White);
		selectedOptionIndex--;
		options[selectedOptionIndex].setFillColor(sf::Color::Yellow);
	}
}

void Menu::moveDown()
{
	if (selectedOptionIndex + 1 < options.size())
	{
		options[selectedOptionIndex].setFillColor(sf::Color::White);
		selectedOptionIndex++;
		options[selectedOptionIndex].setFillColor(sf::Color::Yellow);
	}
}