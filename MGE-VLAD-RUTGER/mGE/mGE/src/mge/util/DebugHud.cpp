#include <cassert>
#include <iostream>
using namespace std;

#include <cstdio>
#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include "mge/core/FPS.hpp"


#include "mge/util/DebugHud.hpp"
#include "mge/config.hpp"

DebugHud::DebugHud( sf::RenderWindow * aWindow )
:	_window( aWindow )
{
	assert ( _window != NULL );

    if (!_font.loadFromFile(config::MGE_FONT_PATH+ "arial.ttf")) {
        cout << "Could not load font, exiting..." << endl;
        return;
    }

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

void DebugHud::draw()
{
	//glDisable( GL_CULL_FACE );
	glActiveTexture(GL_TEXTURE0);
    _window->pushGLStates();
    _window->draw(_debugText);
    _window->draw(_winText);
	_window->draw(_renderTimeText);
	_window->draw(_updateTimeText);
	_window->draw(_triangleCountText);
	_window->draw(_drawCallsText);
	_window->popGLStates();
}
