#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include "glm.hpp"
#include "mge/core/collision/Collider.h"
#include "mge/core/collision/Collision.h"

class BoxCollider : public Collider
{
    public:
        BoxCollider(const glm::vec3 pMinBounds, const glm::vec3 pMaxBounds);
        virtual ~BoxCollider();

        Collision collide(Collider * pCollider);
        Collision collide(BoxCollider * pBoxCol);
        Collision collide(SphereCollider * pSphereCol);

        void translate(const glm::vec3 pTranslation);

        bool isColliding = false;
        float colDistance = 0;

        inline const glm::vec3 getMinBounds() const { return _minBounds; }
        inline const glm::vec3 getMaxBounds() const { return _maxBounds; }

    protected:
    private:
        glm::vec3 _minBounds;
        glm::vec3 _maxBounds;

};

#endif // BOXCOLLIDER_H
