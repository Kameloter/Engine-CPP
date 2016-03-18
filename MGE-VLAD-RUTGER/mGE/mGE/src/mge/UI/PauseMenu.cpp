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

	continueButton.loadFromFile(config::MGE_TEXTURE_PATH + "continueButton.png");
	continueButtonH.loadFromFile(config::MGE_TEXTURE_PATH + "continueButtonH.png");
	quitButton.loadFromFile(config::MGE_TEXTURE_PATH + "quitButton.png");
	quitButtonH.loadFromFile(config::MGE_TEXTURE_PATH + "quitButtonH.png");

	overlay.loadFromFile(config::MGE_TEXTURE_PATH + "pauseMenuOverlay.png");

	//pauseMenuOverlay.loadFromFile(config::MGE_TEXTURE_PATH + "mainMenu_background.png");
	s_ContinueButton.setTexture(continueButton);
	s_ContinueButtonH.setTexture(continueButtonH);
	s_QuitButton.setTexture(quitButton);
	s_QuitButtonH.setTexture(quitButtonH);
	s_overlay.setTexture(overlay);
	//s_overlay.setPosition(SCREEN_WIDTH / 2 - overlay.getSize().x / 2, 0);
	//s_MenuBackground.setTexture(pauseMenuOverlay);
	
	if (!defaultFont.loadFromFile(config::MGE_FONT_PATH + "arial.ttf")) {
		cout << "Could not load font, exiting..." << endl;
		return;
	}

	continueBcacheWIDTH = s_ContinueButton.getTexture()->getSize().x;
	continueBCacheHEIGHT = s_ContinueButton.getTexture()->getSize().y;
	continueBcacheX = 150;
	continueBCacheY = 150;
	s_ContinueButton.setPosition(continueBcacheX, continueBCacheY);
	s_ContinueButtonH.setPosition(continueBcacheX, continueBCacheY);


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
	if (!ButtonPressed(continueBcacheX, continueBCacheY, continueBcacheWIDTH, continueBCacheHEIGHT)) { startHighlight = false; return false; }

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
	_window->draw(s_overlay);
	if (startHighlight)
		_window->draw(s_ContinueButtonH);
	else
		_window->draw(s_ContinueButton);

	if (quitHighlight)
		_window->draw(s_QuitButtonH);
	else
		_window->draw(s_QuitButton);
	_window->popGLStates();

}
