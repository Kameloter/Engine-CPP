#include <cassert>
#include <iostream>
using namespace std;
#include <cstdio>
#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include "MainMenu.h"
#include "mge/config.hpp"

MainMenu::MainMenu(sf::RenderWindow* window) :
	_window(window)
{
	assert(_window != NULL);

	startButton.loadFromFile(config::MGE_TEXTURE_PATH + "button.png");
	startButtonH.loadFromFile(config::MGE_TEXTURE_PATH + "buttonH.png");
	
	s_StartButton.setTexture(startButton);
	s_StartButtonH.setTexture(startButtonH);

	if (!defaultFont.loadFromFile(config::MGE_FONT_PATH + "arial.ttf")) {
		cout << "Could not load font, exiting..." << endl;
		return;
	}
	
}


MainMenu::~MainMenu()
{
}

bool MainMenu::ButtonPressed(int x, int y, int width , int height)
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

bool MainMenu::StartButtonPressed(int x, int y, std::string text)
{
	buttonText.setString(text);
	buttonText.setFont(defaultFont);
	buttonText.setCharacterSize(24);

	buttonText.setPosition(x, y);
	buttonText.setOrigin(0, 0);
	buttonText.setColor(sf::Color::White);

	int width = buttonText.getLocalBounds().width + 10;
	int height = buttonText.getLocalBounds().height + 20;

	s_StartButton.setPosition(x, y);
	s_StartButtonH.setPosition(x, y);

	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();
	if(startHighlight)
		_window->draw(s_StartButtonH);
	else
		_window->draw(s_StartButton);
	_window->draw(buttonText);
	_window->popGLStates();

	if (!ButtonPressed(x, y, width, height)) { startHighlight = false; return false; }

	startHighlight = true;

	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

bool MainMenu::QuitButtonPressed(int x, int y, std::string text)
{



	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}
