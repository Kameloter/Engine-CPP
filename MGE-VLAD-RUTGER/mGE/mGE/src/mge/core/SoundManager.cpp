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
	std::cout << "loaded sound -> " << key << std::endl;
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

void SoundManager::StopSound(std::string key)
{
	std::cout << " key  " << key << std::endl;
	map<std::string, Sound*>::iterator soundIter = _sounds.find(key);
	if (soundIter == _sounds.end())
	{
		std::cout << " error playing sound ... check if key is correct." << std::endl;
		return;
	}
	else {
		soundIter->second->Stop();
	}
}

void SoundManager::EditSound(std::string key, float volume, glm::vec3 pos, bool loop)
{
	map<std::string, Sound*>::iterator soundIter = _sounds.find(key);
	if (soundIter == _sounds.end())
	{
		std::cout << " error playing sound ... check if key is correct." << std::endl;
		return;
	}
	else
	{
		soundIter->second->setLooping(loop);
		soundIter->second->setVolume(volume);
		soundIter->second->setPosition(sf::Vector3f(pos.x,pos.y,pos.z));
	}

}

bool SoundManager::IsPlaying(std::string key)
{
	map<std::string, Sound*>::iterator soundIter = _sounds.find(key);
	if (soundIter == _sounds.end())
	{
		std::cout << " error playing sound ... check if key is correct." << std::endl;
		return false;
	}
	return soundIter->second->isPlaying;
}

void SoundManager::LoadSounds()
{
	//game sounds
	LoadSound(config::MGE_SOUND_PATH + "victory.wav","coin");
	LoadSound(config::MGE_SOUND_PATH + "ambience.wav", "ambience");
	EditSound("ambience", 10, glm::vec3(0),true);

	LoadSound(config::MGE_SOUND_PATH + "Click_Open Menu.wav", "Menu Open");
	LoadSound(config::MGE_SOUND_PATH + "Closing Menu.wav", "Menu Close");

	//LoadSound(config::MGE_SOUND_PATH + "Coins.wav", "Coins");

	LoadSound(config::MGE_SOUND_PATH + "Falling Bridge.wav", "falling bridge");
	LoadSound(config::MGE_SOUND_PATH + "Footstep #1.wav", "footstep1");
	LoadSound(config::MGE_SOUND_PATH + "Footstep #2.wav", "foorstep2");

	LoadSound(config::MGE_SOUND_PATH + "Key.wav", "key");
	//EditSound("key", 25);
	
	LoadSound(config::MGE_SOUND_PATH + "Death.wav", "death");

	LoadSound(config::MGE_SOUND_PATH + "Gate.wav", "gate");

	LoadSound(config::MGE_SOUND_PATH + "Lava.wav", "lava");
	LoadSound(config::MGE_SOUND_PATH + "mechanic click.wav", "mechclick");

	//LoadSound(config::MGE_SOUND_PATH + "Moving Statue.wav", "statue");
//	EditSound("key", 25, true);

	LoadSound(config::MGE_SOUND_PATH + "Pushing Block.wav", "pushingblock");

	LoadSound(config::MGE_SOUND_PATH + "Tension Sound.wav", "tension");


	//NARRATIVE sounds
	LoadSound(config::MGE_SOUND_PATH + "Subtitles_01.wav", "Subtitles_01");

	LoadSound(config::MGE_SOUND_PATH + "Finds Key.wav", "findkey");

	LoadSound(config::MGE_SOUND_PATH + "Nice.wav", "Subtitles_04");

	LoadSound(config::MGE_SOUND_PATH + "Intro HUB.wav", "intro");
	LoadSound(config::MGE_SOUND_PATH + "Search Room.wav", "searchroom");
	LoadSound(config::MGE_SOUND_PATH + "Cross Bridge LVL2.wav", "checkpoint_trigger_06");
	LoadSound(config::MGE_SOUND_PATH + "That was close.wav", "close");
	LoadSound(config::MGE_SOUND_PATH + "Nearby Ghost.wav", "checkpoint_trigger_03");
	//LoadSound(config::MGE_SOUND_PATH + "Tension Sound.wav", "tension");
	//LoadSound(config::MGE_SOUND_PATH + "Tension Sound.wav", "tension");
	//LoadSound(config::MGE_SOUND_PATH + "Tension Sound.wav", "tension");
	//LoadSound(config::MGE_SOUND_PATH + "Tension Sound.wav", "tension");
	//LoadSound(config::MGE_SOUND_PATH + "Tension Sound.wav", "tension");
	//LoadSound(config::MGE_SOUND_PATH + "Tension Sound.wav", "tension");
	//LoadSound(config::MGE_SOUND_PATH + "Tension Sound.wav", "tension");
	//LoadSound(config::MGE_SOUND_PATH + "Tension Sound.wav", "tension");
	//LoadSound(config::MGE_SOUND_PATH + "Tension Sound.wav", "tension");
	//LoadSound(config::MGE_SOUND_PATH + "Tension Sound.wav", "tension");
	//LoadSound(config::MGE_SOUND_PATH + "Tension Sound.wav", "tension");
	//LoadSound(config::MGE_SOUND_PATH + "Tension Sound.wav", "tension");
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

