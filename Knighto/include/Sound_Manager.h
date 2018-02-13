#pragma once
#include "Resource_Manager.h"
#include <SFML\Audio.hpp>

class Sound_Manager :public Resource_Manager
{
private:
	std::map<std::string, sf::SoundBuffer> sounds;
	std::map<std::string, sf::Music> songs;
public:
	void load(const std::string& name, const std::string& filename);
	sf::SoundBuffer& getRef(const std::string& sound);
	//sf::Music& getRef(const std::string& song);
	Sound_Manager() {}
};
