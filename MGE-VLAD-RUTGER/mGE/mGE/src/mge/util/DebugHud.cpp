#include <cassert>
#include <iostream>
using namespace std;

#include <cstdio>
#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include "mge/core/FPS.hpp"

#include "mge/core/Timer.hpp"
#include "mge/util/DebugHud.hpp"
#include "mge/config.hpp"
#include "mge/StatsHolder.h"
#include "mge/core/FadeManager.h"

DebugHud::DebugHud( sf::RenderWindow * aWindow )
:	_window( aWindow )
{
	_alpha = 1;

	_fade = true;
	_startFade = false;
	   
	_fadeStartTime = 0;



	assert ( _window != NULL );

    if (!_font.loadFromFile(config::MGE_FONT_PATH+ "arial.ttf")) {
        cout << "Could not load font, exiting..." << endl;
        return;
    }

	_loadingScreen.loadFromFile(config::MGE_TEXTURE_PATH + "loadingScreen.png");
	s_LoadingScreen.setTexture(_loadingScreen);
	s_LoadingScreen.setPosition(0, 0);

	fadeBlack.loadFromFile(config::MGE_TEXTURE_PATH + "fadeblack.png");
	s_fadeBlack.setTexture(_loadingScreen);

    _createDebugHud();
}

DebugHud::~DebugHud()
{
	//dtor
}

void DebugHud::_createDebugHud() {
    _debugText.setString("");
    _debugText.setFont(_font);
	_debugText.setCharacterSize(16);
	_debugText.setColor(sf::Color::White);

    _winText.setString("");
    _winText.setFont(_font);
	_winText.setCharacterSize(16);
	_winText.setColor(sf::Color::White);

	_renderTimeText.setString("");
	_renderTimeText.setFont(_font);
	_renderTimeText.setCharacterSize(12);
	_renderTimeText.setColor(sf::Color::White);


	_updateTimeText.setString("");
	_updateTimeText.setFont(_font);
	_updateTimeText.setCharacterSize(12);
	_updateTimeText.setColor(sf::Color::White);


	_triangleCountText.setString("");
	_triangleCountText.setFont(_font);
	_triangleCountText.setCharacterSize(12);
	_triangleCountText.setColor(sf::Color::White);

	_drawCallsText.setString("");
	_drawCallsText.setFont(_font);
	_drawCallsText.setCharacterSize(12);
	_drawCallsText.setColor(sf::Color::White);


}

void DebugHud::setDebugInfo(std::string pInfo) {
    _debugText.setString(pInfo);
	_debugText.setPosition(10, 10);
}

void DebugHud::setWinTextInfo(std::string pInfo) {
    _winText.setString(pInfo);
	_winText.setPosition(10 ,100);
}

void DebugHud::setPerformanceDebugInfo(std::string renderTime, std::string updateTime, std::string triangleCount, std::string drawCalls)
{
	_renderTimeText.setString(renderTime);
	_renderTimeText.setPosition(10, 30);

	_updateTimeText.setString(updateTime);
	_updateTimeText.setPosition(10, 50);

	_triangleCountText.setString(triangleCount);
	_triangleCountText.setPosition(10, 70);

	_drawCallsText.setString(drawCalls);
	_drawCallsText.setPosition(10, 90);

}

void DebugHud::showLoadingScreen()
{
	s_LoadingScreen.setPosition(0, 0);
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();
	_window->draw(s_LoadingScreen);
	_window->popGLStates();
	_window->display();

}

void DebugHud::disableLoadingScreen()
{
	s_LoadingScreen.setPosition(0, 2000);
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();
	_window->draw(s_LoadingScreen);
	_window->popGLStates();
	_window->display();
	
}

void DebugHud::updateAlpha()
{
	if (_startFade)
	{
		if (_fade)
		{
			//dynamic_cast<FadeScreenMaterial*>(_fadeScreen->getMaterial())->setRenderImage(true);
			if ((Timer::now() - _fadeStartTime) < 2)
			{
				_alpha += 0.02;
				if (_alpha > 1)
					_alpha = 1;
				//decrease fade.

				s_fadeBlack.setColor(sf::Color(255, 255, 255, _alpha / 255));


			}
			else {

				_startFade = false;
			}

		}
		else
		{
			if ((Timer::now() - _fadeStartTime) < 2)
			{

				_alpha -= 0.02;
				if (_alpha < 0)
					_alpha = 0;
				//decrease fade.
				s_fadeBlack.setColor(sf::Color(255, 255, 255, _alpha / 255));

			}
			else
			{
				//dynamic_cast<FadeScreenMaterial*>(_fadeScreen->getMaterial())->setRenderImage(false);
				_startFade = false;
			}
		}
	}
}

void DebugHud::setFade(bool value)
{
	//_fade = value;
	//_startFade = true;
	//_fadeStartTime = Timer::now();
}





void DebugHud::draw()
{
	//zupdateAlpha();

	//glDisable( GL_CULL_FACE );
	glActiveTexture(GL_TEXTURE0);
    _window->pushGLStates();


    _window->draw(_debugText);
    _window->draw(_winText);
	_window->draw(_renderTimeText);
	_window->draw(_updateTimeText);
	_window->draw(_triangleCountText);
	_window->draw(_drawCallsText);
	//_window->draw(s_LoadingScreen);
	//_window->draw(s_fadeBlack);
	_window->popGLStates();
}
