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
		sound.setBuffer(buffer);
		return true;
	}
	
}

void Sound::Play(bool stop)
{
	sound.play();
}

void Sound::setLooping(bool value)
{
	sound.setLoop(value);
}
