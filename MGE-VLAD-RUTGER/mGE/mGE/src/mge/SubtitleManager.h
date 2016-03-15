#pragma once
#include <SFML\Graphics.hpp>
#include "glm.hpp"
class Subtitle;
class SubtitleManager
{


public:

	
	SubtitleManager() {}
	
	static void createSubtitles();
	static void update(float pStep);
	static void playSubtitle(std::string sub,glm::vec2 pTextPos, sf::Color pTextColor = sf::Color::White);
	static void playSubtitle(std::string sub, sf::Color pTextColor = sf::Color::White);
	static void draw(sf::RenderWindow * pWindow);
	static void resetText(std::string s, float t);
	static void addSubtitle(std::string pGameObject, std::string pSubtitle, float showtime);

private:

	static sf::Font _subFont;
	static sf::Text _subText;

	static std::map<std::string, Subtitle*> _subtitles;

};

