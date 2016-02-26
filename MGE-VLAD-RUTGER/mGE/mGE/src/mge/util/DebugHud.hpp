#ifndef DEBUGHUD_H
#define DEBUGHUD_H

#include <SFML/Graphics.hpp>
#include <iostream>

class DebugHud
{
	public:
		DebugHud( sf::RenderWindow * aWindow );
		virtual ~DebugHud();
		void draw();

		void setDebugInfo (std::string pInfo);
		void setWinTextInfo (std::string pInfo);


		void playSubTitle();
	private:
		sf::RenderWindow * _window;

        std::string _debugInfo;

        sf::Font _font;
        sf::Text _debugText;
        sf::Text _winText;


		sf::Text _subToShow;

        void _createDebugHud();
};

#endif // DEBUGHUD_H
