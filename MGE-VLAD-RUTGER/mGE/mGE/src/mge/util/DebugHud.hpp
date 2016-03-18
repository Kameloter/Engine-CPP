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

		void setPerformanceDebugInfo(std::string renderTime, std::string updateTime, std::string triangleCount, std::string drawCalls);
		void showLoadingScreen();
		void disableLoadingScreen();


		void updateAlpha();
		void setFade(bool value);
	
	private:
		float _alpha;

		 bool _fade;
		 bool _startFade;

		 float _fadeStartTime;
		sf::RenderWindow * _window;

        std::string _debugInfo;

        sf::Font _font;
        sf::Text _debugText;
        sf::Text _winText;
		sf::Text _renderTimeText;
		sf::Text _updateTimeText;
		sf::Text _triangleCountText;
		sf::Text _drawCallsText;
		sf::Text _subToShow;
		sf::Texture _loadingScreen;
		sf::Sprite s_LoadingScreen;
        void _createDebugHud();

		sf::Texture fadeBlack;
		sf::Sprite s_fadeBlack;
};

#endif // DEBUGHUD_H
