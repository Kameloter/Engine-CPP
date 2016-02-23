#include "FPCamera.h"
#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>

FPCamera::FPCamera(float pMoveSpeed, float pTurnSpeed, GameObject * pPlayer,sf::Window * pWindow)
{
    _moveSpeed = pMoveSpeed;
    _turnSpeed = pTurnSpeed;
    _player = pPlayer;
    _window = pWindow;

}

FPCamera::~FPCamera()
{
    //dtor
}
void FPCamera::update(float pStep){

	if (!_inAction) {
		glm::mat4 ownerTransform = _owner->getTransform();

		sf::Vector2i mouseVector = sf::Mouse::getPosition();
		sf::Mouse::setPosition((sf::Vector2i(_window->getPosition().x + _window->getSize().x / 2, _window->getPosition().y + _window->getSize().y / 2)));

		sf::Vector2i diffVector = -(mouseVector - sf::Mouse::getPosition());

		ownerTransform = glm::rotate(ownerTransform, diffVector.y / 500.0f, glm::vec3(1.0f, 0, 0));
		_player->rotate(diffVector.x / 500.0f, glm::vec3(0, 1.0f, 0));

		glm::vec3 forward = glm::normalize(glm::vec3(-ownerTransform[2]));

		float angle = glm::degrees(glm::angle(glm::vec3(forward.x, 0, forward.z), forward));

		if (angle <= 80) {
			_owner->setTransform(ownerTransform);
		}
	}
	else
	{
		glm::mat4 ownerTransform = _owner->getTransform();

		sf::Vector2i mouseVector = sf::Mouse::getPosition();
		sf::Mouse::setPosition((sf::Vector2i(_window->getPosition().x + _window->getSize().x / 2, _window->getPosition().y + _window->getSize().y / 2)));

		sf::Vector2i diffVector = -(mouseVector - sf::Mouse::getPosition());

		ownerTransform = glm::rotate(ownerTransform, diffVector.y / 500.0f, glm::vec3(1.0f, 0, 0));
		_player->rotate(diffVector.x / 500.0f, glm::vec3(0, 1.0f, 0));

		glm::vec3 forward = glm::normalize(glm::vec3(-ownerTransform[2]));
	

		float angleY = glm::degrees(glm::angle(glm::vec3(forward.x, 0, forward.z), forward));
/*
		float angleX = glm::degrees(glm::angle(forward, glm::vec3(0,0,1) ));*/

		if (angleY <= 80) {
			_owner->setTransform(ownerTransform);
		}
		
	}
}
