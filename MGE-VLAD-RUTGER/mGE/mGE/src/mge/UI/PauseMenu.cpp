#include <cassert>
#include <iostream>
using namespace std;
#include <cstdio>
#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include "PauseMenu.h"
#include "mge/config.hpp"

PauseMenu::PauseMenu(sf::RenderWindow* window) :
	_window(window)
{
	assert(_window != NULL);
	SCREEN_HEIGHT = _window->getSize().y;
	SCREEN_WIDTH = _window->getSize().x;

	startButton.loadFromFile(config::MGE_TEXTURE_PATH + "startButton.png");
	startButtonH.loadFromFile(config::MGE_TEXTURE_PATH + "startButtonH.png");
	quitButton.loadFromFile(config::MGE_TEXTURE_PATH + "quitButton.png");
	quitButtonH.loadFromFile(config::MGE_TEXTURE_PATH + "quitButtonH.png");

	menuBackground.loadFromFile(config::MGE_TEXTURE_PATH + "mainMenu_background.png");
	s_StartButton.setTexture(startButton);
	s_StartButtonH.setTexture(startButtonH);
	s_QuitButton.setTexture(quitButton);
	s_QuitButtonH.setTexture(quitButtonH);
	s_MenuBackground.setTexture(menuBackground);
	//s_MenuBackground.setPosition(0, 0);

	if (!defaultFont.loadFromFile(config::MGE_FONT_PATH + "arial.ttf")) {
		cout << "Could not load font, exiting..." << endl;
		return;
	}

	startBcacheWIDTH = s_StartButton.getTexture()->getSize().x;
	startBCacheHEIGHT = s_StartButton.getTexture()->getSize().y;
	startBcacheX = 150;
	startBCacheY = 150;
	s_StartButton.setPosition(startBcacheX, startBCacheY);
	s_StartButtonH.setPosition(startBcacheX, startBCacheY);


	quitBcacheWIDTH = s_QuitButton.getTexture()->getSize().x;
	quitBCacheHEIGHT = s_QuitButton.getTexture()->getSize().y;
	quitBcacheX = 200;
	quitBCacheY = 350;
	s_QuitButton.setPosition(quitBcacheX, quitBCacheY);
	s_QuitButtonH.setPosition(quitBcacheX, quitBCacheY);
	
	/*s_QuitButton.setPosition(x, y);
	s_QuitButtonH.setPosition(x, y);*/

}


PauseMenu::~PauseMenu()
{
}

bool PauseMenu::ButtonPressed(int x, int y, int width , int height)
{

	

	/*sf::RectangleShape rect(sf::Vector2f(width, height));
	rect.setPosition(x, y);
	rect.setFillColor(sf::Color::Blue);
*/
	

	sf::Vector2i mousePos( sf::Mouse::getPosition(*_window).x , sf::Mouse::getPosition(*_window).y); // window is a sf::Window
	//cout <<" X " <<  mousePos.x << "  Y " <<  mousePos.y << endl;

	if (mousePos.x < x) return false;
	if (mousePos.y < y) return false;
	if (mousePos.x > x + width) return false;
	if (mousePos.y > y + height) return false;


	
	


}

bool PauseMenu::StartButtonPressed()
{
	if (!ButtonPressed(startBcacheX, startBCacheY, startBcacheWIDTH, startBCacheHEIGHT)) { startHighlight = false; return false; }

	startHighlight = true;

	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

bool PauseMenu::QuitButtonPressed()
{
	if (!ButtonPressed(quitBcacheX, quitBCacheY, quitBcacheWIDTH, quitBCacheHEIGHT)) { quitHighlight = false; return false; }

	quitHighlight = true;

	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void PauseMenu::update()
{
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();
	_window->draw(s_MenuBackground);
	if (startHighlight)
		_window->draw(s_StartButtonH);
	else
		_window->draw(s_StartButton);

	if (quitHighlight)
		_window->draw(s_QuitButtonH);
	else
		_window->draw(s_QuitButton);
	_window->popGLStates();

}
