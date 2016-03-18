#include "TriggerManager.h"
#include "mge/core/collision/Collision.h"
#include "mge/core/GameObject.hpp"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include <algorithm>
TriggerManager::TriggerManager()
{
    //ctor
}

TriggerManager::~TriggerManager()
{
    //dtor
}

void TriggerManager::addStaticTrigger(GameObject * object)
{
	_triggers.push_back(object);
}
void TriggerManager::addMovingTrigger(GameObject * object)
{
	_movingTriggers.push_back(object);
}
void TriggerManager::cleanStaticObject(GameObject * object)
{
	//std::cout << " Cleaning individual object trigger from list "<< std::endl;
	std::cout << " Static trig count " << _triggers.size() << std::endl;
	_triggers.erase(std::remove(_triggers.begin(), _triggers.end(), object), _triggers.end());
	std::cout << " Static trig count " << _triggers.size() << std::endl;
}

void TriggerManager::cleanMovingObject(GameObject * object)
{
	std::cout << " Moving Trig count " << _movingTriggers.size() << std::endl;
	_movingTriggers.erase(std::remove(_movingTriggers.begin(), _movingTriggers.end(), object), _movingTriggers.end());
	std::cout << " Moving Trig count " << _movingTriggers.size() << std::endl;
}




std::vector<GameObject*> TriggerManager::getStaticTriggerObjects()
{
	//std::cout << "Returning size of static trigger objects  " << _triggers.size() << std::endl;
	return _triggers;
}

void TriggerManager::cleanUp()
{
	_triggers.clear();
	//_triggers.shrink_to_fit();
	_movingTriggers.clear();
	//_movingTriggers.shrink_to_fit();
	std::cout << " Triggers and moving triggers cleared " << std::endl;
}
void TriggerManager::runPhysics(float pDelta)
{
//	std::cout << " Helo trig" <<  std::endl;
    for(unsigned int i = 0; i < _movingTriggers.size(); i++)
    {
		//std::cout << " Helo rb  " << std::endl;
	//	std::cout << " Helo rb  " << _movingTriggers[i]->getTrigger()->getMaxBounds() <<  std::endl;
        for(unsigned int j = 0; j < _triggers.size(); j++)
        {

		//	std::cout << " Helo sb" << std::endl;
			//std::cout << _movingTriggers[i]->getTrigger()->getMaxBounds() << std::endl;
			//maybe it should return a pointer and then delete it at end of collision loop after giving info to objects???

			
			Collision collisionInfo = _movingTriggers[i]->getTrigger()->resolveCollision(_triggers[j]->getTrigger());
			
            if(collisionInfo.getIsColliding())
            {
				collisionInfo.setInfo(true, _movingTriggers[i]);
                //  std::cout << "THERE IS COLLISION " << std::endl;
			/*	  _movingTriggers[i]->getTrigger()->collisionInfo->setInfo(true, _triggers[j]->getName());
				  _triggers[j]->getTrigger()->collisionInfo->setInfo(true, _movingTriggers[i]->getName());*/

				_movingTriggers[i]->getBehaviour()->OnCollision(collisionInfo);
				_triggers[j]->getBehaviour()->OnCollision(collisionInfo);
			}
			else 
			{
				/*_movingTriggers[i]->getTrigger()->collisionInfo->setInfo(false,"");
				_triggers[j]->getTrigger()->collisionInfo->setInfo(false, "");*/
			}
        }
    }
}
