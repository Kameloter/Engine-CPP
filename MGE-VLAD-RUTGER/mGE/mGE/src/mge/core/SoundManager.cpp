#include "SoundManager.h"
#include "Sound.h"
#include "mge/config.hpp"

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

void SoundManager::LoadSound(std::string pFilename,std::string key)
{
	Sound * sound = 0;
	map<std::string, Sound*>::iterator soundIter = _sounds.find(key);
	if (soundIter == _sounds.end()) {
	
		sound = _loadFromFile(pFilename);
		std::cout << "Sound :" << pFilename << " - with key " << key << " - loaded." << std::endl;
		std::cout << "Caching texture." << std::endl;
		_sounds[key] = sound;
	}
	else {
		std::cout << "Returning cached sound :" << pFilename << std::endl;
		sound = soundIter->second;
	}
}

void SoundManager::PlaySound(std::string key)
{
	std::cout << " key  " << key << std::endl;
	map<std::string, Sound*>::iterator soundIter = _sounds.find(key);
	if (soundIter == _sounds.end())
	{
		std::cout << " error playing sound ... check if key is correct." << std::endl;
		return;
	}
	else {
		soundIter->second->Play();
	}
	
}

void SoundManager::LoadSounds()
{
	LoadSound(config::MGE_SOUND_PATH + "victory.wav","coin");
	//LoadSound(config::MGE_SOUND_PATH + "coin.wav", "coun");
	//LoadSound(config::MGE_SOUND_PATH + "coin.wav", "coun");
	//LoadSound(config::MGE_SOUND_PATH + "coin.wav", "coun");
	//LoadSound(config::MGE_SOUND_PATH + "coin.wav", "coun");
}

Sound* SoundManager::_loadFromFile(std::string pFileName)
{
	Sound * sound = new Sound();
	if (!sound->Load(pFileName)) {
		std::cout << " failed to load sound ... ok doei !" << std::endl;
		return 0;
	}
	return sound;
}

