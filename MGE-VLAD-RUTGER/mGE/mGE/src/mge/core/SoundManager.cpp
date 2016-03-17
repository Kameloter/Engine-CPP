#include "SoundManager.h"
#include "Sound.h"


SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

void SoundManager::LoadSound(std::string pFilename,std::string key)
{
	Sound * sound = 0;

	map<std::string, Sound*>::iterator soundIter = _sounds.find(pFilename);
	if (soundIter == _sounds.end()) {
		sound->Load(pFilename);
		std::cout << "Sound :" << pFilename << " - loaded." << std::endl;
		std::cout << "Caching texture." << std::endl;
		_sounds[pFilename] = sound;
	}
	else {
		std::cout << "Returning cached texture :" << pFilename << std::endl;
		sound = soundIter->second;
	}
}
