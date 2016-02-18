#ifndef COLLIDER_H
#define COLLIDER_H
#include <glm.hpp>
#include "Collision.h"
class BoxCollider;
class SphereCollider;
class Collider
{
    public:
        Collider();
        virtual ~Collider();
        Collision* collisionInfo;


        virtual Collision collide(Collider * pCollider) = 0;
        virtual Collision collide(BoxCollider * pBoxCol) = 0;
        virtual Collision collide(SphereCollider * pSphereCol) = 0;

        virtual void translate(const glm::vec3 pTranslation) = 0;

    protected:

        Collision resolveCollision (BoxCollider * colA, BoxCollider * colB);
        Collision resolveCollision (BoxCollider * colA, SphereCollider * colB);
        Collision resolveCollision (SphereCollider * colA, SphereCollider * colB);
};

#endif // COLLIDER_H
