#include <glm.hpp>
#include "mge/behaviours/FPController.h"
#include "mge/behaviours/FPCamera.h"
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "mge/core/collision/RigidbodyGameObject.h"
#include "mge/core/Timer.hpp"

GameObject* _camera;
neV3 jump;
FPController::FPController(float pMoveSpeed, float pTurnSpeed, GameObject * pCamera, InputType pInputType):
	startTime(0)
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

bool _canPress = false;

float minimaly = 0;
void FPController::update(float pStep) {
	neV3 rv;
	rv.Set(dynamic_cast<RigidbodyGameObject*>(_owner)->GetRigidBody()->GetVelocity());
	glm::vec3 rbVel(rv[0], rv[1], rv[2]);
	/*if (rbVel != glm::vec3(0))
	{
		std::cout << "Player vel " << rbVel << std::endl;
	}*/


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
				startTime = Timer::now();
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _canPress && _grounded /*&& glm::abs(rbVel.y) < 0.05f*/) {

				dynamic_cast<RigidbodyGameObject*>(_owner)->GetRigidBody()->ApplyImpulse(jump);
				startTime = Timer::now();
				_grounded = false;
				_canPress = false;
			}

			break;

		}

		if (glm::length(translate) != 0) {
			dynamic_cast<RigidbodyGameObject*>(_owner)->moveRb(translate);
			minimaly = rbVel.y;
		}
	
		//std::cout << Timer::now() << std::endl;
		if (Timer::now() > startTime + 2)
		{
			_grounded = true;
		}

		dynamic_cast<FPCamera*>(_camera->getBehaviour())->_inAction = _inAction;

	}
}



