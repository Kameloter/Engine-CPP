#pragma once

#include "SFML\Graphics.hpp"
#include <iostream>
using namespace std;

class MainMenu
{
public:
	MainMenu(sf::RenderWindow* window);
	~MainMenu();
	sf::Font defaultFont;
	sf::Text buttonText;

 bool ButtonPressed(int x, int y, std::string text); 

private:
 sf::RenderWindow* _window;
};

