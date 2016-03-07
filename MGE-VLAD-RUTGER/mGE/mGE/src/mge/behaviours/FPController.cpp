#include <glm.hpp>
#include "mge/behaviours/FPController.h"
#include "mge/behaviours/FPCamera.h"
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "mge/core/collision/RigidbodyGameObject.h"
GameObject* _camera;
neV3 jump;
FPController::FPController(float pMoveSpeed, float pTurnSpeed, GameObject * pCamera, InputType pInputType)
{
    _moveSpeed = pMoveSpeed;
    _turnSpeed = pTurnSpeed;
    _camera = pCamera;
    _inputType = pInputType;
	jump.Set(0, 70, 0);

}

FPController::~FPController()
{

}
bool _grounded = true;
bool _canPress = false;

void FPController::update(float pStep){

	if (!_inAction) {
		glm::vec3 translate;
		glm::vec3 camForward = _owner->getForward();//glm::normalize(glm::vec3(_camera->getForward().x,0,_camera->getForward().z));
		glm::vec3 camRight = _owner->getRight();// glm::normalize(glm::vec3(_camera->getRight().x,0,_camera->getRight().z));
		switch (_inputType)
		{

		case InputType::ArrowKeys:

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) translate += camForward * 0.1f * _moveSpeed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) translate -= camForward * 0.1f* _moveSpeed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) translate -= camRight * 0.1f * _moveSpeed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))translate += camRight * 0.1f* _moveSpeed;

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				_canPress = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _canPress && _grounded) {
				translate.y += 4;
				_grounded = false;
				_canPress = false;
			}
			break;
		case InputType::WASD:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) translate += camForward* 0.1f * _moveSpeed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) translate -= camForward* 0.1f * _moveSpeed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) translate -= camRight* 0.1f * _moveSpeed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) translate += camRight * 0.1f* _moveSpeed;

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				_canPress = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _canPress && _grounded) {

				dynamic_cast<RigidbodyGameObject*>(_owner)->GetRigidBody()->ApplyImpulse(jump);
				_grounded = true;
				_canPress = false;
			}

			break;

		}
		if (glm::length(translate) != 0) {
			dynamic_cast<RigidbodyGameObject*>(_owner)->moveRb(translate);
		}
		else {
			//dynamic_cast<RigidbodyGameObject*>(_owner)->moveRb(glm::vec3(0, translate.y, 0));
		}
		// std::cout << "FPcontroller Input - > " << translate << std::endl;
   // _owner->translate(translate); // - >> Move character on input.
//    _owner->translate(glm::vec3(0,-0.1f,0)); // -> small gravity;

   // if(_owner->getLocalPosition().y < -5.0f) _owner->setLocalPosition(glm::vec3(0,4,0));
  //  glm::vec3 ownerLocPos  = _owner->getLocalPosition();
//    if (!(ownerLocPos.x > -1.1f && ownerLocPos.x<1.1f && ownerLocPos.z >-1.1f && ownerLocPos.z<1.1f)){
//
//        if(ownerLocPos.y <= 1) _owner->setLocalPosition(glm::vec3(ownerLocPos.x,1,ownerLocPos.z));
//    }

   //  if(ownerLocPos.y >= 1 && ownerLocPos.y < 1.5f) _grounded = true;
	// if(ownerLocPos.y <= 1) _owner->setLocalPosition(glm::vec3(ownerLocPos.x,1,ownerLocPos.z));
//    if(ownerLocPos.y <= -2.0f){
//        _owner->setLocalPosition(glm::vec3(-7,0,0));
//    }

	}

	dynamic_cast<FPCamera*>(_camera->getBehaviour())->_inAction = _inAction;

}



