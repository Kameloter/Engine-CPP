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

 bool ButtonPressed(int x, int y, int width, int height); 

 bool StartButtonPressed(int x, int y, std::string text);
 bool QuitButtonPressed(int x, int y, std::string text);

private:
 sf::RenderWindow* _window;

 bool startHighlight;
 bool quitHighlight;

 sf::Texture startButton;
 sf::Texture quitButton;
 sf::Texture startButtonH;
 sf::Texture quitButtonH;

 sf::Sprite s_StartButton;
 sf::Sprite s_QuitButton;
 sf::Sprite s_StartButtonH;
 sf::Sprite s_QuitButtonH;
};

