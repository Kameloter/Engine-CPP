#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#include "Collision.h"
#include "mge/core/GameObject.hpp"
#include "Rigidbody.h"

class CollisionManager
{
    public:
        CollisionManager();
        virtual ~CollisionManager();

        void addObject (GameObject * pObject);
        void addRbObject (GameObject * pObject);
        inline GameObject* getObjectAt(unsigned int pIndex) const { return _objects[pIndex];}

        void runPhysics(float pDelta);


    protected:
    private:
        void doCollisionCheck();
        std::vector<GameObject*> _objects;
        std::vector<GameObject*> _rbObjects;
};

#endif // COLLISIONMANAGER_H
