#include "EventDispatcher.h"
#include "EventListener.h"
#include <iostream>
std::vector<EventListener*> EventDispatcher::_eventListeners;
EventDispatcher::EventDispatcher()
{

}
EventDispatcher::~EventDispatcher()
{

}


 void EventDispatcher::dispatchEvent(sf::Event pEvent)
{
	for (std::vector<EventListener*>::iterator listener = _eventListeners.begin(); listener != _eventListeners.end(); ++listener)
	{
		(*listener)->OnEvent(pEvent);
	}
}

  void EventDispatcher::registerListener(EventListener * listener)
 {
	 _eventListeners.push_back(listener);
	 std::cout << " Listener registered " << std::endl;
 }
  void EventDispatcher::unRegisterListener(EventListener * listener)
  {
	  _eventListeners.erase(std::remove(_eventListeners.begin(), _eventListeners.end(), listener), _eventListeners.end());
  }