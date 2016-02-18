#include "SphereCollider.h"
#include <iostream>
using namespace std;
SphereCollider::SphereCollider(glm::vec3 pCenter,float pRadius):
    _center(pCenter),_radius(pRadius)
{
    //ctor
}

SphereCollider::~SphereCollider()
{
    //dtor
}
Collision SphereCollider::collide(Collider * pCollider)
{
    cout << "Double dispatch..." << endl;
    return pCollider->collide(this);
}
Collision SphereCollider::collide(BoxCollider * pBoxCol)
{
    cout << "SphereCol.collides (BoxCol)" << endl;
    return Collider::resolveCollision(pBoxCol, this);
}

Collision SphereCollider::collide(SphereCollider * pSphereCol)
{
    cout << "SphereCol.collides (SphereCol)" << endl;
    return Collider::resolveCollision(this, pSphereCol);
}

void SphereCollider::translate(const glm::vec3 pTranslation)
{
    _center += pTranslation;
}
