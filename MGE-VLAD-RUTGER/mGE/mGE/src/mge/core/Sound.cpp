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
}

void Sound::setLooping(bool value)
{
	sound.setLoop(value);
}
