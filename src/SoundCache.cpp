#pragma once

#include "SoundCache.h"

SoundCache::SoundCache()
{
	loadSounds();
}

void SoundCache::play(const std::string & name)
{
	sounds[name].play();
}

void SoundCache::loadFromFile(const std::string& name, const std::string& file)
{
	soundBuffers[name].loadFromFile(file);
	sounds[name].setBuffer(soundBuffers[name]);
}

void SoundCache::loadSounds()
{
	loadFromFile("appleCatch", "data/sounds/appleCatch.ogg");
	loadFromFile("menuMove", "data/sounds/menuMove.ogg");
	loadFromFile("menuSelect", "data/sounds/menuSelect.ogg");
	loadFromFile("fail", "data/sounds/fail.ogg");
}