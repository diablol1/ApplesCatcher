#pragma once

#include <SFML/Audio.hpp>

#include <iostream>
#include <map>


class SoundManager
{
public:
	SoundManager();

	void play(const std::string& name);
private:
	std::map<std::string, sf::SoundBuffer> soundBuffers;
	std::map<std::string, sf::Sound> sounds;

	void loadFromFile(const std::string& name, const std::string& file);
	void loadSounds();
};