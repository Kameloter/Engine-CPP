#pragma once
#include "SFML\Graphics.hpp"

class EventListener;
class EventDispatcher
{
public:
	EventDispatcher();
	~EventDispatcher();

	static void dispatchEvent(sf::Event pEvent);

	static void registerListener(EventListener * listener);
	static void unRegisterListener(EventListener * listener);

private:
	static std::vector<EventListener*> _eventListeners;


};