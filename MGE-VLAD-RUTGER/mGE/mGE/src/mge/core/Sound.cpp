#include "Sound.h"

Sound::Sound()
{

}

Sound::~Sound()
{

}

bool Sound::Load(std::string fileName)
{
	if (!buffer.loadFromFile(fileName))
	{
		std::cout << " WRONG SOUND NAME !" << std::endl;
		return false;
	}
	else 
	{
		std::cout << "loaded sound " << std::endl;
		sound.setBuffer(buffer);
		return true;
	}
	
}

void Sound::Play(bool stop)
{
	if (stop)
		sound.stop();
	std::cout << "playing sound " << std::endl;
	sound.play();
	isPlaying = true;
}

void Sound::Stop()
{
	sound.stop();
	isPlaying = false;
}

void Sound::setLooping(bool value)
{
	sound.setLoop(value);
}

void Sound::setVolume(int amount)
{
	sound.setVolume(amount);
}

void Sound::setPosition(sf::Vector3f pos)
{
	sound.setPosition(pos);
	sound.setMinDistance(5.0f);
	sound.setAttenuation(10.0f);
	std::cout << sound.getPosition().x << sound.getPosition().y<< sound.getPosition().z<< std::endl;
	//sound.setRelativeToListener(true);
}
