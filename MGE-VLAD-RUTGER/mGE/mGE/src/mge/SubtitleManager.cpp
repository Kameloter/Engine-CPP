#include "SubtitleManager.h"
#include "mge\Subtitle.h"
#include <cassert>
#include <iostream>
using namespace std;

#include <cstdio>
#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include "mge/config.hpp"

sf::Text SubtitleManager::_subText;

sf::Font SubtitleManager::_subFont;

std::map<std::string, Subtitle*> SubtitleManager::_subtitles;

bool showSubtitle = false;
float waitTime = 0.0f;
float timer = 0.0f;


void SubtitleManager::createSubtitles()
{
	/*Subtitle* sub = new Subtitle("HELLO I AM NEW SUBTITLE AND IM SO NICE :)");
	Subtitle* sub2 = new Subtitle("HELLO I AM NEW SUBTITLE AND IM SO NICE :)");
	Subtitle* sub3 = new Subtitle("HELLO I AM NEW SUBTITLE AND IM SO NICE :)");
	Subtitle* sub4 = new Subtitle("HELLO I AM NEW SUBTITLE AND IM SO NICE :)");*/
}


void SubtitleManager::update(float pStep)
{
	if (showSubtitle && waitTime > 0)
	{
		timer += pStep;
		if (timer >= waitTime)
		{
			timer = 0.0f;
			resetText("", 0);
			showSubtitle = false;
		}
	}
}

void SubtitleManager::resetText(std::string s, float t)
{
	_subText.setString(s);
	waitTime = t;
	showSubtitle = true;
}


 void SubtitleManager::addSubtitle(std::string pGameObject, std::string pSubtitle)
{
	Subtitle * sub = 0;

	std::map<std::string, Subtitle*>::iterator subIterator = _subtitles.find(pGameObject);

	if (subIterator == _subtitles.end()) 
	{
		sub = new Subtitle(pSubtitle);
		std::cout << "Subtitle for object ->  " << pGameObject << " loaded. With content \n  " <<
			pSubtitle << std::endl;
	
		_subtitles[pGameObject] = sub;
	}
	else {
		std::cout << "Subtitle already added. Noob !!" << std::endl;
	}
}

void SubtitleManager::playSubtitle(std::string sub, float showTime)
{
	Subtitle * sub2 = 0;
	std::map<std::string, Subtitle*>::iterator myIter = _subtitles.find(sub);
	if (myIter == _subtitles.end()) // if iterator is at the end then he did not find existing mesh
	{
		std::cout << " no sub like dat bro  .. returning" << std::endl;
		return;
	}
	else {
		sub2 = myIter->second;
	}
	

	//std::map<std::string, Subtitle*>::iterator meshIterator = _subtitles.find(sub);
	
	_subFont.loadFromFile(config::MGE_FONT_PATH + "arial.ttf");
	_subText.setFont(_subFont);
	_subText.setString(sub2->subtitle);
	_subText.setPosition(sf::Vector2f(10, 10));
	_subText.setColor(sf::Color::White);


	waitTime = showTime;
	showSubtitle = true;

}
void SubtitleManager::draw(sf::RenderWindow * pWindow)
{
	glActiveTexture(GL_TEXTURE0);
	
	pWindow->pushGLStates();
	pWindow->draw(_subText);

	pWindow->popGLStates();
}
