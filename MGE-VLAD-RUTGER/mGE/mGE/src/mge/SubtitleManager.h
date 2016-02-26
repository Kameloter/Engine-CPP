#pragma once
#include <SFML\Graphics.hpp>
class Subtitle;
class SubtitleManager
{


public:

	
	SubtitleManager() {}
	
	static void createSubtitles();
	static void update(float pStep);
	static void playSubtitle(std::string sub, float showTime);
	static void draw(sf::RenderWindow * pWindow);
	static void resetText(std::string s, float t);
	static void addSubtitle(std::string pGameObject, std::string pSubtitle);

private:

	static sf::Font _subFont;
	static sf::Text _subText;

	static std::map<std::string, Subtitle*> _subtitles;

};

