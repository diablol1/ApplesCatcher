#include "TextureManager.h"

bool TextureManager::add(const std::string& _name, const std::string & _path)
{
	sf::Texture tmpTexture;
	tmpTexture.loadFromFile(_path);

	for (const auto& texture : textures)
	{
		if (texture.first == _name)
		{
			std::cout << "Texture manager contains texture with name: " + _name;
			return  false;
		}
	}

	textures[_name] = tmpTexture;

	for (const auto& path : paths)
	{
		if (path == _path)
		{
			std::cout << "Texture managers contains textur with path: " + _path;
			return false;
		}
	}
	paths.push_back(_path);

	return true;
}