#include "mge/behaviours/KeysBehaviour2.hpp"
#include "mge/core/GameObject.hpp"

#include <sfml/window/event.hpp>

KeysBehaviour2::KeysBehaviour2(float moveSpeed, float turnSpeed): AbstractBehaviour(), _moveSpeed(moveSpeed), _turnSpeed(turnSpeed)
{
}

KeysBehaviour2::~KeysBehaviour2()
{
}

void KeysBehaviour2::update( float pStep )
{
	float moveSpeed = 0.0f; //default if no keys
	float moveSpeed2 = 0.0f;
	float moveSpeed3 = 0.0f;
	float turnSpeed = 0.0f;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W )) {
		moveSpeed = _moveSpeed;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S )) {
		moveSpeed = -_moveSpeed;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D )) {
		moveSpeed2 = -_moveSpeed;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A )) {
		moveSpeed2 = _moveSpeed;
	}

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Q )) {
		moveSpeed3 = -_moveSpeed;
	}
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::E )) {
		moveSpeed3 = _moveSpeed;
	}
	//translate the object in its own local space
	_owner->translate( glm::vec3(moveSpeed2*pStep,moveSpeed3 * pStep , moveSpeed*pStep ) );

	//we can also translate directly, basically we take the z axis from the matrix
	//which is normalized and multiply it by moveSpeed*step, than we add it to the
	//translation component
	//glm::mat4 transform = _owner->getTransform();
	//transform[3] += transform[2] * moveSpeed*pStep;
	//_owner->setTransform(transform);

	//rotate the object in its own local space
	_owner->rotate( glm::radians(turnSpeed*pStep), glm::vec3(0.0f, 1.0f, 0.0f ) );
}
