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

	if (!defaultFont.loadFromFile(config::MGE_FONT_PATH + "arial.ttf")) {
		cout << "Could not load font, exiting..." << endl;
		return;
	}
	
}


MainMenu::~MainMenu()
{
}

bool MainMenu::ButtonPressed(int x, int y, std::string text)
{
	buttonText.setString(text);
	buttonText.setFont(defaultFont);
	buttonText.setCharacterSize(24);

	buttonText.setPosition(x, y);
	buttonText.setOrigin(0, 0);
	buttonText.setColor(sf::Color::White);
	
	int width = buttonText.getLocalBounds().width + 10;
	int height = buttonText.getLocalBounds().height + 20;

	sf::RectangleShape rect(sf::Vector2f(width, height));
	rect.setPosition(x, y);
	rect.setFillColor(sf::Color::Blue);

	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();
	_window->draw(rect);
	_window->draw(buttonText);
	_window->popGLStates();

	sf::Vector2i mousePos( sf::Mouse::getPosition(*_window).x , sf::Mouse::getPosition(*_window).y); // window is a sf::Window
	//cout <<" X " <<  mousePos.x << "  Y " <<  mousePos.y << endl;

	if (mousePos.x < x) return false;
	if (mousePos.y < y) return false;
	if (mousePos.x > x + width) return false;
	if (mousePos.y > y + height) return false;

	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}
