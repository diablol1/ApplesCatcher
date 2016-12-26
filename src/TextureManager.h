#pragma once

#include <string>
#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
class TextureManager
{
public:
	bool add(const std::string& name, const std::string& path);

	sf::Texture& get(const std::string& name) {
		return textures[name];
	}
private:
	std::map<std::string, sf::Texture> textures;
	std::vector<std::string> paths;
};