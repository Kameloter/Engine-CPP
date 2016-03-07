#include "StatueBehaviour.h"
#include "mge/core/collision/RigidbodyGameObject.h"
#include "mge/core/collision/StaticGameObject.h"
#include "mge/behaviours/FPController.h"

#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>



StatueBehaviour::StatueBehaviour()
{
	_isCarried = false;
}

StatueBehaviour::~StatueBehaviour()
{
}

void StatueBehaviour::update(float pStep) {
	
	//if (glm::distance(_owner->getLocalPosition(), _player->getLocalPosition())<5.0f) {

	//	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
	//		_canPress = true;
	//	}
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && _canPress) {
	//		if (_isCarried) {
	//			_isCarried = false;
	//			dynamic_cast<FPController*>(_player->getBehaviour())->_inAction = false;
	//		}
	//		else {
	//			_isCarried = true;
	//			dynamic_cast<FPController*>(_player->getBehaviour())->_inAction = true;
	//		}
	//		_canPress = false;
	//	}
	//	if (_isCarried) {
	//		glm::vec3 diffVector = glm::normalize(_owner->getLocalPosition() - _player->getLocalPosition());
	//		
	//		neRigidBody * rigidbody = dynamic_cast<RigidbodyGameObject*>(_player)->GetRigidBody();

	//		glm::vec3 posi = _owner->getLocalPosition();// + _player->getForward() * 4;
	//		glm::vec3 direction;

	//		if (diffVector.z > 0 && diffVector.x < 0.7f && diffVector.x > -0.7f) {
	//			posi += _owner->getForward() * 3;
	//			direction = glm::vec3(0, 0, 1);
	//		
	//		}
	//		else if (diffVector.z < 0 && diffVector.x < 0.7f && diffVector.x > -0.7f) {
	//			posi += -_owner->getForward() * 3;
	//			direction = glm::vec3(0, 0, -1);
	//		}
	//		else if (diffVector.z > -0.7f && diffVector.z < 0.7f && diffVector.x <0.0f) {
	//			posi += _owner->getRight() * 3;
	//			direction = glm::vec3(-1, 0, 0);
	//		}
	//		else if (diffVector.z > -0.7f && diffVector.z < 0.7f && diffVector.x >0.0f) {
	//			posi += -_owner->getRight() * 3;
	//			direction = glm::vec3(1, 0, 0);
	//		}

	//	/*	if (glm::distance(_owner->getLocalPosition(), _player->getLocalPosition())>4) {
	//			_isCarried = false;
	//			dynamic_cast<FPController*>(_player->getBehaviour())->_inAction = false;
	//		}*/

	//		neV3 pos;
	//		pos.Set(posi.x, _player->getLocalPosition().y, posi.z);
	//		rigidbody->SetPos(pos);

	//		glm::vec3 movement(direction.x * 3, 0, direction.z * 3);

	//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dynamic_cast<StaticGameObject*>(_owner)->moveStaticObject(movement/200);
	//	}
	//}

	//_owner->translate(glm::vec3(0, -0.5f, 0)); // -> small gravity;
	//glm::vec3 ownerLocPos = _owner->getLocalPosition();
	//if (ownerLocPos.y <= .25f && !_isCarried) _owner->setLocalPosition(glm::vec3(ownerLocPos.x, .25f, ownerLocPos.z));
}

void StatueBehaviour::SetPlayer(GameObject * pPlayer)
{
	_player = pPlayer;
}
