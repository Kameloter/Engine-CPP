#pragma once
#include <map>
#include <iostream>

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

	void LoadSounds();

private:
	Sound * _loadFromFile(std::string pFileName);
	map<string, Sound*> _sounds;

	static SoundManager * _instance;
};

