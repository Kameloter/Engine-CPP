#include "BoxCollider.h"
#include <iostream>

using namespace std;
BoxCollider::BoxCollider(const glm::vec3 pMinBounds, const glm::vec3 pMaxBounds) :
    _minBounds(pMinBounds),_maxBounds(pMaxBounds)
{
    //ctor
}

BoxCollider::~BoxCollider()
{
    //dtor
}

void BoxCollider::translate(const glm::vec3 pTranslation)
{
    _minBounds += pTranslation;
    _maxBounds += pTranslation;
}


Collision BoxCollider::collide(Collider * pCollider)
{
    // cout << "Double dispatch..." << endl;
    return pCollider->collide(this);
}
Collision BoxCollider::collide(BoxCollider * pBoxCol)
{
   // cout << "BoxCol.collides (BoxCol)" << endl;
    return Collider::resolveCollision(this,pBoxCol);
}
Collision BoxCollider::collide(SphereCollider * pSphereCol)
{
  // cout << "BoxCol.collides (pSphereCol)" << endl;
    return Collider::resolveCollision(this,pSphereCol);
}
