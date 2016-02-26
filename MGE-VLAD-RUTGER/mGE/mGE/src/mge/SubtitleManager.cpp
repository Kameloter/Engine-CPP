#include "SubtitleManager.h"
#include "mge\Subtitle.h"

sf::Text SubtitleManager::_subText;
sf::Font SubtitleManager::_subFont;
std::map<std::string, Subtitle*> SubtitleManager::_subtitles;

bool showSubtitle = false;
float waitTime = 0.0f;
float timer = 0.0f;


void SubtitleManager::createSubtitles()
{
	Subtitle* sub = new Subtitle("HELLO I AM NEW SUBTITLE AND IM SO NICE :)");
	Subtitle* sub2 = new Subtitle("HELLO I AM NEW SUBTITLE AND IM SO NICE :)");
	Subtitle* sub3 = new Subtitle("HELLO I AM NEW SUBTITLE AND IM SO NICE :)");
	Subtitle* sub4 = new Subtitle("HELLO I AM NEW SUBTITLE AND IM SO NICE :)");
}


void SubtitleManager::update(float pStep)
{
	if (showSubtitle && waitTime > 0)
	{
		timer += pStep;
		if (timer >= waitTime)
		{
			timer = 0.0f;
			// hide text
			showSubtitle = false;
		}
	}
}


void SubtitleManager::playSubtitle(std::string sub, float showTime)
{
	std::map<std::string, Subtitle*>::iterator meshIterator = _subtitles.find(sub);


}
void SubtitleManager::draw(sf::RenderWindow * pWindow)
{

}
