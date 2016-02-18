#include <glm.hpp>
#include "FollowBehaviour.h"
#include "mge/core/GameObject.hpp"

#include <iostream>

FollowBehaviour::FollowBehaviour(GameObject * pTarget): AbstractBehaviour(), _target(pTarget)
{
    //ctor
}

FollowBehaviour::~FollowBehaviour()
{
    //dtor
}
void FollowBehaviour::update( float step )
{

    glm::mat4 targetMat = _target->getTransform();
    _owner->setTransform(glm::mat4(-targetMat[0],targetMat[1],-targetMat[2],glm::vec4(_target->getLocalPosition() + glm::vec3(0,1,0),1)));
}


