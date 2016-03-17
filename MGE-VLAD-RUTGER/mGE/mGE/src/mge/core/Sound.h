#pragma once
#include "SFML\Audio.hpp"
#include <iostream>

class Sound {

public:
	
	Sound();
	~Sound();

	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music music;

	bool Load(std::string fileName);
	void Play(bool stop = true);
	void setLooping(bool value);

private:
	

};
