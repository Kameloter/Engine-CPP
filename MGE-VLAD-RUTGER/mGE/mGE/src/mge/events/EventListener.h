#pragma once
#include "SFML\Graphics.hpp"

class EventListener {
public:
	EventListener();
	virtual ~EventListener();

	virtual void OnEvent(sf::Event pEvent) = 0;
};
 