#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include <iostream>
using namespace std;

Collider::Collider()
{
    //ctor
}

Collider::~Collider()
{
    //dtor
}


Collision Collider::resolveCollision (BoxCollider * colA, BoxCollider * colB)
{

   // cout << "Solving Box to Box" << endl;
    glm::vec3 distance1 = colB->getMinBounds() - colA->getMaxBounds();
    glm::vec3 distance2 = colA->getMinBounds() - colB->getMaxBounds();
    //cout << "CubeB - Min bounds " << colB->getMinBounds() << endl;
    //cout << "CubeB - Max bounds " << colB->getMaxBounds() << endl;
  //  cout << "CubeA - Min bounds " << colA->getMinBounds() << endl;
   // cout << "CubeA - Max bounds " << colA->getMaxBounds() << endl;

   // cout << "distance1 (bMin - Amax) " << distance1 << endl;
    //cout << "distance2 (aMin - bMax) " << distance2 << endl;

    glm::vec3 distanceEachAxis = glm::max(distance1,distance2);
  //  cout << "glm max (dist1, dist2) " << distanceEachAxis << endl;
    float maxDist = distanceEachAxis[0];


    for(int i = 0; i < 3 ; i++)
    {
        if(distanceEachAxis[i] > maxDist)
        {
            maxDist = distanceEachAxis[i];
        }
    }
    //cout << "MAX DISTANCE -> " << maxDist << endl;
  //  cout << "IS COLLIDING -> " << (maxDist < 0) << endl;
    return Collision(maxDist < 0,maxDist);
}
Collision Collider::resolveCollision (BoxCollider * colA, SphereCollider * colB)
{
      //cout << "Solving Box to Sphere" << endl;
    return Collision(false,10);
}
Collision Collider::resolveCollision (SphereCollider * colA, SphereCollider * colB)
{
    //  cout << "Solving Sphere to Sphere" << endl;
    return Collision(false,10);
}
