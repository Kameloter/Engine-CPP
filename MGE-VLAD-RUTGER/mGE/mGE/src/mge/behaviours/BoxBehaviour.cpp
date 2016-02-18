#include "BoxBehaviour.h"

#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>

BoxBehaviour::BoxBehaviour(GameObject * player)
{
    _player = player;
    _isCarried = false;
    //ctor
}

BoxBehaviour::~BoxBehaviour()
{
    //dtor
}

void BoxBehaviour::update(float pStep){
  if (glm::distance(_owner->getWorldPosition(), _player->getWorldPosition())<2.0f){

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
		_canPress = true;
	}
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::E ) && _canPress) {
            if(_isCarried){
                _isCarried = false;
            }else{
                _isCarried = true;
            }
            _canPress = false;
    }
    if (_isCarried) _owner->setLocalPosition(_player->getLocalPosition() + _player->getForward() * 10.0f);
  }

    _owner->translate(glm::vec3(0,-0.5f,0)); // -> small gravity;
    glm::vec3 ownerLocPos  = _owner->getLocalPosition();
    if(ownerLocPos.y <= .25f && !_isCarried) _owner->setLocalPosition(glm::vec3(ownerLocPos.x,.25f,ownerLocPos.z));
}
