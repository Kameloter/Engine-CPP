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

 bool StartButtonPressed();
 bool QuitButtonPressed();

 void update();
private:
 sf::RenderWindow* _window;
 float SCREEN_WIDTH;
 float SCREEN_HEIGHT;
 float startBcacheX;
 float startBCacheY;
 float startBcacheWIDTH;
 float startBCacheHEIGHT;

 float quitBcacheX;
 float quitBCacheY;
 float quitBcacheWIDTH;
 float quitBCacheHEIGHT;

 bool startHighlight;
 bool quitHighlight;

 sf::Texture startButton;
 sf::Texture quitButton;
 sf::Texture startButtonH;
 sf::Texture quitButtonH;
 sf::Texture menuBackground;

 sf::Sprite s_StartButton;
 sf::Sprite s_QuitButton;
 sf::Sprite s_StartButtonH;
 sf::Sprite s_QuitButtonH;
 sf::Sprite s_MenuBackground;
};

