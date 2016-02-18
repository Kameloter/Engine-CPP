#include "DoorBehaviour.h"

#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>

DoorBehaviour::DoorBehaviour()
{
    _activated = false;

}

DoorBehaviour::~DoorBehaviour()
{
    //dtor
}

void DoorBehaviour::update(float pStep){
    if (_activated){
        std::cout<<glm::distance(_owner->getWorldPosition(), _openPos)<<std::endl;
       if (glm::distance(_owner->getWorldPosition(), _openPos)>0.25f){
           _owner->translate(glm::vec3(0,.01,0));
       }
    }
}

void DoorBehaviour::InitializePositions(glm::vec3 translateUp){
    _closedPos = _owner->getLocalPosition();
    _openPos = _owner->getLocalPosition() + translateUp;
    std::cout<<_closedPos<<std::endl;
    std::cout<<_openPos<<std::endl;
}
