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

private:

	static sf::Font _subFont;
	static sf::Text _subText;

	static std::map<std::string, Subtitle*> _subtitles;

};

