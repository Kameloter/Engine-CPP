#ifndef TRIGGERMANAGER_H
#define TRIGGERMANAGER_H
#include <iostream>
#include <vector>

class StaticGameObject;
class GameObject;
class RigidbodyGameObject;
class TriggerManager
{
    public:
        TriggerManager();
        virtual ~TriggerManager();

        void addStaticTrigger(GameObject * pObject);
		void addMovingTrigger(GameObject * pObject);
		void cleanUp();
		/*void addObject(StaticGameObject * pObject);

        void addRbObject (RigidbodyGameObject * pObject);*/
       // inline StaticGameObject* getStaticObjectAt(unsigned int pIndex) const { return _objects[pIndex];}
		//inline RigidbodyGameObject* getRigidbodyObjectAt(unsigned int pIndex) const { return _rbObjects[pIndex]; }
        void runPhysics(float pDelta);

		
    protected:
    private:
        
		std::vector<GameObject*> _triggers;
		std::vector<GameObject*> _movingTriggers;
};

#endif // TRIGGERMANAGER_H

