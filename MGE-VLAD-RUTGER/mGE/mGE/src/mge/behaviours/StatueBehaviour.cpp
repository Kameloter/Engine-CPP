#include "StatueBehaviour.h"
#include "mge/core/collision/RigidbodyGameObject.h"
#include "mge/core/collision/StaticGameObject.h"
#include "mge/behaviours/FPController.h"

#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>

#include "mge/core/SoundManager.h"



StatueBehaviour::StatueBehaviour()
{

}

StatueBehaviour::~StatueBehaviour()
{
}

bool activate = false;
void StatueBehaviour::update(float pStep) {

	/*if (oldPos != glm::vec3(0, 0, 0)) {
		glm::vec3 difVector = oldPos - _owner->getLocalPosition();
		std::cout << activate << std::endl;

		if (glm::length(difVector) > 0 && !activate) {
			activate = true;
		}

		if (activate) {
			timer += pStep;
			if (timer > 2.0f) {
				activate = false;
				timer = 0.0f;
			}
		}


	}




	oldPos = _owner->getLocalPosition();*/
	//if (lenght != 0) {
	//	
	//	//std::cout << timer << std::endl;
	//	timer = 0.0f;
	//	if (!SoundManager::getInstance().IsPlaying("statue")) {
	//		SoundManager::getInstance().PlaySound("statue");
	//	}
	//}
	//else
	//{
	////	std::cout << timer << std::endl;
	//	timer += pStep;
	//	if (SoundManager::getInstance().IsPlaying("statue") && timer >= 3.0f) {
	//		SoundManager::getInstance().StopSound("statue");
	//		timer = 0.0f;
	//	}
	//	
	//}
}

