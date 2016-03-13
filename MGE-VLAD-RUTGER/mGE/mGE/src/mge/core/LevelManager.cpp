//World , components , managers
#include "LevelManager.h"
#include "mge/core/World.hpp"
#include "mge/core/collision/PhysicsWorld.h"
#include "mge/core/Mesh.hpp"
#include "mge/LUA/LUAManager.h"
#include "mge/core/Camera.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/xml/XmlReader.h"
//Lights and gameobjects
#include "mge/core/GameObject.hpp"
#include "mge/core/Player.h"
#include "mge/core/collision/RigidbodyGameObject.h"
#include "mge/core/collision/StaticGameObject.h"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/core/light/Light.h"
#include "mge/core/light/DirectionalLight.h"
#include "mge/core/light/PointLight.h"
#include "mge/core/light/SpotLight.h"

//Additional materials
#include "mge/materials/TextureNormalMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureLitMaterial.hpp"

//Behaviours 
#include "mge/behaviours/StatueBehaviour.h"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour2.hpp"
#include "mge/behaviours/FPController.h"
#include "mge/behaviours/BoxBehaviour.h"
#include "mge/behaviours/DoorBehaviour.h"
#include "mge/behaviours/TriggerBehaviour.h"
#include "mge/behaviours/FPCamera.h"
#include "mge/behaviours/LookAt.hpp"
#include "mge/behaviours/Orbit.hpp"
#include "SFML\Audio.hpp"
//Util
#include "mge/util/Color.h"
#include "mge/config.hpp"
#include "mge\core\Timer.hpp"
#include "mge/SubtitleManager.h"

LevelManager::LevelManager() 
{
	cout << "Current level at start -> " << currentlevel << endl;
}

LevelManager::~LevelManager()
{

}

void LevelManager::SwitchToLevel(GameLevels pToLevel)
{
	if (currentlevel == pToLevel)
		return;

	DestroyLevel(currentlevel);
	std::cout << "destroyed level" << currentlevel  <<std::endl;
	
	BuildLevel(pToLevel);
	currentlevel = pToLevel;
}
void LevelManager::ReloadLevel()
{
	DestroyLevel(currentlevel);
	BuildLevel(currentlevel);
}
void LevelManager::BuildLevel(GameLevels pLevel)
{
	switch (pLevel)
	{
	case Menu:
		Build_menu();
		break;
	case HUB:
		Build_level_hub();
		break;
	case HUBTUTORIAL:
		Build_level_hub_tutorial();
		break;
	case Level1:
		Build_level_1();
		break;
	case Level2:
		Build_level_2();
		break;
	case Level3:
		Build_level_3();
		break;
	case Level4:
		Build_level_4();
		break;
	default:
		break;
	}
}

void LevelManager::DestroyLevel(GameLevels pLevel)
{
	switch (pLevel)
	{
	case Menu:
		cout << " Menu destroyed " << endl;

		_world->CleanUpPhysicsWorld();
		//cleanup menu
		break;
	case HUB:
		cout << " HUB destroyed " << endl;
		_world->CleanUpPhysicsWorld();
		// Do something special so hub doesnt get destroyed completely
		// or maybe store info in a class and use that info to create it again (so doors are closed after you complete level 1 )
		break;

	case HUBTUTORIAL:
		cout << " HUB destroyed " << endl;
		_world->CleanUpPhysicsWorld();
		// Do something special so hub doesnt get destroyed completely
		// or maybe store info in a class and use that info to create it again (so doors are closed after you complete level 1 )
		break;
	case Level1:
		cout << " Level 1 destroyed " << endl;
		_world->CleanUpPhysicsWorld();
		break;
	case Level2:
		cout << " Level 2 destroyed " << endl;
		_world->CleanUpPhysicsWorld();
		break;
	case Level3:
		cout << " Level 3 destroyed " << endl;
		_world->CleanUpPhysicsWorld();
		break;
	case Level4:
		cout << " Level 4 destroyed " << endl;
		_world->CleanUpPhysicsWorld();
		break;
	default:
		break;
	}
}

void LevelManager::Build_menu()
{
	cout << " Menu Build " << endl;
}
float subStartTime = 0;
float lastSubTime = 0;
bool tutorialStart = false;


void LevelManager::Build_level_hub()
{
	DirectionalLight * light = new DirectionalLight("light", glm::vec3(40, 5, 35), glm::vec3(-1, 1, -0.5f), glm::vec3(0.05), glm::vec3(0.05), glm::vec3(0.1f));
	_world->add(light);
	_world->AddLight(light);

	XmlReader * xmlReader = new XmlReader(_world);
	xmlReader->LoadLevel("level_hub");
	xmlReader->LoadInteractables("interactables_level_hub2");
	xmlReader->LoadSubtitleTriggers("triggers_level_hub");

	tutorialStart = true;
	LUAManager::InitializeFile(_world,"level_hub");
}

void LevelManager::Build_level_hub_tutorial()
{
	DirectionalLight * light = new DirectionalLight("light", glm::vec3(40, 5, 35), glm::vec3(-1, 1, -0.5f), glm::vec3(0.05), glm::vec3(0.05), glm::vec3(0.1f));
	_world->add(light);
	_world->AddLight(light);

	XmlReader * xmlReader = new XmlReader(_world);
	xmlReader->LoadLevel("level_hub");
	xmlReader->LoadInteractables("interactables_level_hub");
	xmlReader->LoadSubtitleTriggers("triggers_level_hub");

	tutorialStart = true;
	LUAManager::InitializeFile(_world, "level_hub");
}

sf::SoundBuffer ambientBuffer;
sf::Sound soundAmbient;

void LevelManager::Build_level_1()
{	
	DirectionalLight * light = new DirectionalLight("light", glm::vec3(40, 5, 35), glm::vec3(-1, 1, -0.5f), glm::vec3(0.05), glm::vec3(0.05), glm::vec3(0.1f));
	_world->add(light);
	_world->AddLight(light);

	cout << " Build level 1 " << endl;

	XmlReader * xmlReader = new XmlReader(_world);
	xmlReader->LoadLevel("level_01");
	xmlReader->LoadInteractables("interactables");
	xmlReader->LoadSubtitleTriggers("triggers_level_01");
	LUAManager::InitializeFile(_world,"level_01");
	
	//if (!ambientBuffer.loadFromFile(config::MGE_SOUND_PATH + "ambience.wav"))
	//{
	//	std::cout << " cant load sound " << std::endl;
	//}
	//soundAmbient.setBuffer(ambientBuffer);
	//soundAmbient.setLoop(true);
	//soundAmbient.play();

}

void LevelManager::Build_level_2()
{
	DirectionalLight * light = new DirectionalLight("light", glm::vec3(40, 5, 35), glm::vec3(-1, 1, -0.5f), glm::vec3(0.05), glm::vec3(0.05), glm::vec3(0.1f));
	_world->add(light);
	_world->AddLight(light);

	XmlReader * xmlReader = new XmlReader(_world);
	xmlReader->LoadLevel("level_02");
	xmlReader->LoadInteractables("interactables_level_02");
	xmlReader->LoadSubtitleTriggers("triggers_level_02");
	LUAManager::InitializeFile(_world,"level_02");
}

void LevelManager::Build_level_3()
{
	XmlReader * xmlReader = new XmlReader(_world);
	xmlReader->LoadLevel("level_03");
	xmlReader->LoadInteractables("interactables_level_03");
	xmlReader->LoadSubtitleTriggers("triggers_level_03");
	//LUAManager::InitializeFile(_world);
}

void LevelManager::Build_level_4()
{
	Light *dirLight = new DirectionalLight("Directional Light", glm::vec3(0, 0, 0), glm::vec3(0, -1, 2), glm::vec3(0.3), glm::vec3(1), glm::vec3(1));
	_world->add(dirLight);
	_world->AddLight(dirLight);

	XmlReader * xmlReader = new XmlReader(_world);
	xmlReader->LoadLevel("level_04");
	xmlReader->LoadInteractables("interactables_level_04");
	xmlReader->LoadSubtitleTriggers("triggers_level_04");
	//LUAManager::InitializeFile(_world);

	std::cout << "LOADED level 4 bIATIHT" << std::endl;
}
bool s_1 = false;
bool s_2 = false;
bool s_3 = false;
bool s_4 = false;
bool s_5 = false;

void LevelManager::testUpdate()
{
	if (tutorialStart) {
		if (Timer::now() > subStartTime + 5 && !s_1)
		{
			SubtitleManager::playSubtitle("HUB_01");
			subStartTime = Timer::now();
			s_1 = true;

		}
		else  if (Timer::now() > subStartTime + 10 && !s_2)

		{
			SubtitleManager::playSubtitle("Tutorial_01", true);
			subStartTime = Timer::now();
			s_2 = true;
		}
		else  if (Timer::now() > subStartTime + 10 && !s_3)

		{
			SubtitleManager::playSubtitle("HUB_02");
			subStartTime = Timer::now();
			s_3 = true;
		}
		else  if (Timer::now() > subStartTime + 10 && !s_4)

		{
			SubtitleManager::playSubtitle("HUB_03");
			subStartTime = Timer::now();
			s_4 = true;
		}
		else  if (Timer::now() > subStartTime + 10 && !s_5)

		{
			SubtitleManager::playSubtitle("Tutorial_02", true);
			subStartTime = Timer::now();
			s_5 = true;
		}

	}
}

void LevelManager::setWorldWindow(PhysicsWorld * pWorld, sf::Window * pWindow)
{
	_world = pWorld;
	_window = pWindow;
}

