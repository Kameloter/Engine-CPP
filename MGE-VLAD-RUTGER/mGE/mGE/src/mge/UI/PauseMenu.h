#pragma once

#include "SFML\Graphics.hpp"
#include <iostream>
using namespace std;

class PauseMenu
{
public:
	PauseMenu(sf::RenderWindow* window);
	~PauseMenu();
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
 float continueBcacheX;
 float continueBCacheY;
 float continueBcacheWIDTH;
 float continueBCacheHEIGHT;

 float quitBcacheX;
 float quitBCacheY;
 float quitBcacheWIDTH;
 float quitBCacheHEIGHT;
 

 bool startHighlight;
 bool quitHighlight;
 sf::Texture overlay;
 sf::Sprite s_overlay;

 sf::Texture continueButton;
 sf::Texture quitButton;
 sf::Texture continueButtonH;
 sf::Texture quitButtonH;


 sf::Sprite s_ContinueButton;
 sf::Sprite s_QuitButton;
 sf::Sprite s_ContinueButtonH;
 sf::Sprite s_QuitButtonH;

};

