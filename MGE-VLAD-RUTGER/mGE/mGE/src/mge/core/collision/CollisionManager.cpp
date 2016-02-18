#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
    //ctor
}

CollisionManager::~CollisionManager()
{
    //dtor
}

void CollisionManager::addObject(GameObject * pObject)
{
    _objects.push_back(pObject);
}
void CollisionManager::addRbObject(GameObject * pObject)
{
    _rbObjects.push_back(pObject);
}

void CollisionManager::runPhysics(float pDelta)
{
    for(unsigned int i = 0; i < _objects.size(); i++)
    {
        //apply gravity if the rigidbody is not kinematic. etc

    }

    doCollisionCheck();
}

void CollisionManager::doCollisionCheck()
{
    //std::cout << "col size" << _objects.size() << std::endl;
    for(unsigned int i = 0; i < _rbObjects.size(); i++)
    {
       // std::cout << "First obj -> " << _objects[i]->getName() << std::endl;
        for(unsigned int j = 0; j < _objects.size(); j++)
        {
         //    std::cout << "Second obj -> " << _objects[j]->getName() << std::endl;
          //   std::cout << "Testing for " << j << " collisions." << std::endl;


            Collision collisionInfo = _rbObjects[i]->getCollider()->collide(_objects[j]->getCollider());

           // std :: cout << "After colliding bool " << collisionInfo.getIsColliding() << std::endl;
          //  std :: cout << "After colliding distance " << collisionInfo.getCollisionDistance() << std::endl;
            if(collisionInfo.getIsColliding())
            {
                  //std::cout << "THERE IS COLLISION " << std::endl;

                glm::vec3 collisionDirection = glm::normalize(
                        _rbObjects[i]->getLocalPosition() - _objects[j]->getLocalPosition()) *
                                                          collisionInfo.getCollisionDistance();

                glm::vec3 rbPos = _rbObjects[i]->getLocalPosition();

                 _rbObjects[i]->setLocalPosition(rbPos - collisionDirection);


//                if (glm::abs(collisionDirection.y) > 0.01f)
//                {
//                     _rbObjects[i]->setLocalPosition(glm::vec3(rbPos.x,rbPos.y - collisionDirection.y,rbPos.z));
//                }
//
//                  else if (glm::abs(collisionDirection.z) > 0.01f)
//                {
//                    _rbObjects[i]->setLocalPosition(glm::vec3(rbPos.x,rbPos.y,rbPos.z - collisionDirection.z));
//                }
//                else if (glm::abs(collisionDirection.x) > 0.01f)
//                {
//                    _rbObjects[i]->setLocalPosition(glm::vec3(rbPos.x - collisionDirection.x,rbPos.y,rbPos.z));
//                }





                //std::cout << " colDir " << collisionDirection << std::endl;
               // std::cout << " colDir lenght " << glm::length(collisionDirection) << std::endl;



            }
        }
    }
}
