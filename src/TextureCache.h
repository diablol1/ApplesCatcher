#pragma once

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>


class TextureCache
{
public:
	TextureCache() {
		loadTextures();
	}
	sf::Texture& get(const std::string& name) {
		return textures[name];
	}
private:
	std::map<std::string, sf::Texture> textures;
	std::vector<std::string> paths;

	bool loadFromFile(const std::string& name, const std::string& path);
	void loadTextures();
};