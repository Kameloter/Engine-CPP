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
	sf::Vector3f position;
	bool Load(std::string fileName);
	void Play(bool stop = true);
	void Stop();
	void setLooping(bool value);
	void setVolume(int amount);
	void setPosition(sf::Vector3f pos);
	bool isPlaying = false;

private:
	

};
