#pragma once
#include <map>
#include <iostream>
#include <glm.hpp>


using namespace std;
class Sound;
class SoundManager
{
public:

	static SoundManager& getInstance() {
		static SoundManager  _instance;

		return _instance;
	}

	SoundManager();
	~SoundManager();


	void LoadSound(std::string pFilename, std::string key);
	void PlaySound(std::string key);
	void StopSound(std::string key);
	void EditSound(std::string key, float volume, glm::vec3 pos, bool loop = false);
	bool IsPlaying(std::string key);

	void LoadSounds();

private:
	Sound * _loadFromFile(std::string pFileName);
	map<string, Sound*> _sounds;

	static SoundManager * _instance;
};

