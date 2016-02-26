#include "BoxTrigger.h"
#include <iostream>
#include "mge/core/collision/Collision.h"

using namespace std;
BoxTrigger::BoxTrigger(const glm::vec3 pMinBounds, const glm::vec3 pMaxBounds) :
    _minBounds(pMinBounds),_maxBounds(pMaxBounds)
{
    //ctor

	collisionInfo = new Collision(false,0);
}

BoxTrigger::~BoxTrigger()
{
    //dtor

	delete collisionInfo;
	cout << " collision info cleared" << endl;
}

void BoxTrigger::translate(const glm::vec3 pTranslation)
{
    _minBounds += pTranslation;
    _maxBounds += pTranslation;
	
//	cout <<" Min bounds " <<  _minBounds << endl;
}
Collision BoxTrigger::resolveCollision( BoxTrigger * colB)
{
	glm::vec3 distance1 = colB->getMinBounds() - getMaxBounds();
	glm::vec3 distance2 = getMinBounds() - colB->getMaxBounds();
	//cout << "CubeB - Min bounds " << colB->getMinBounds() << endl;
	//cout << "CubeB - Max bounds " << colB->getMaxBounds() << endl;
//  cout << "CubeA - Min bounds " << getMinBounds() << endl;
 //cout << "CubeA - Max bounds " << getMaxBounds() << endl;

	// cout << "distance1 (bMin - Amax) " << distance1 << endl;
	//cout << "distance2 (aMin - bMax) " << distance2 << endl;

	glm::vec3 distanceEachAxis = glm::max(distance1, distance2);
	//  cout << "glm max (dist1, dist2) " << distanceEachAxis << endl;
	float maxDist = distanceEachAxis[0];


	for (int i = 0; i < 3; i++)
	{
		if (distanceEachAxis[i] > maxDist)
		{
			maxDist = distanceEachAxis[i];
		}
	}
	//cout << "MAX DISTANCE -> " << maxDist << endl;
	//  cout << "IS COLLIDING -> " << (maxDist < 0) << endl;
	return Collision(maxDist < 0, maxDist);
}



