
#include "TriggerBehaviour.h"

#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>

TriggerBehaviour::TriggerBehaviour(GameObject * box, DoorBehaviour * doorBehaviour)
{
    _box = box;
    _activated = false;
    _doorBehaviour = doorBehaviour;
}

TriggerBehaviour::~TriggerBehaviour()
{
    //dtor
}

void TriggerBehaviour::update(float pStep){
  if (glm::distance(_owner->getWorldPosition(), _box->getWorldPosition())<.25f){
      _activated = true;
//      _doorBehaviour->_activated = true;
      //_box->getBehaviour()->

      //_door->getBehaviour().
     // std::cout<<_activated<<std::endl;
  }
}
