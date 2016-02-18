#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "mge/core/collision/Collider.h"


class SphereCollider : public Collider
{
    public:
        SphereCollider(glm::vec3 pCenter, float pRadius);
        virtual ~SphereCollider();

        Collision collide(Collider * pCollider);
        Collision collide(BoxCollider * pBoxCol);
        Collision collide(SphereCollider * pSphereCol);

        void translate(const glm::vec3 pTranslation);
    protected:
    private:
        float _radius;
        glm::vec3 _center;
};

#endif // SPHERECOLLIDER_H
