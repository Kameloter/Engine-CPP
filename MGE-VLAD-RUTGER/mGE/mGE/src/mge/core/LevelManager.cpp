//World , components , managers
#include "LevelManager.h"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/LUA/LUAManager.h"
#include "mge/core/Camera.hpp"
#include "mge/materials/AbstractMaterial.hpp"

//Lights and gameobjects
#include "mge/core/GameObject.hpp"
#include "mge/core/collision/RigidbodyGameObject.h"
#include "mge/core/collision/StaticGameObject.h"
#include "mge/core/light/Light.h"
#include "mge/core/light/DirectionalLight.h"
#include "mge/core/light/PointLight.h"
#include "mge/core/light/SpotLight.h"

//Additional materials
#include "mge/materials/TextureNormalMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureLitMaterial.hpp"

//Behaviours 
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

//Util
#include "mge/util/Color.h"
#include "mge/config.hpp"

LevelManager::LevelManager(World * pWorld):
	_world(pWorld)
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
	switch (pToLevel)
	{
	case Menu:
		BuildLevel(Menu);
		break;
	case HUB:
		BuildLevel(HUB);
		break;
	case Level1:
		BuildLevel(Level1);
		break;
	case Level2:
		BuildLevel(Level2);
		break;
	default:
		break;
	}
	currentlevel = pToLevel;
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
	case Level1:
		Build_level_1();
		break;
	case Level2:
		Build_level_2();
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
		//cleanup menu
		break;
	case HUB:
		cout << " HUB destroyed " << endl;
		// Do something special so hub doesnt get destroyed completely
		// or maybe store info in a class and use that info to create it again (so doors are closed after you complete level 1 )
		break;
	case Level1:
		cout << " Level 1 destroyed " << endl;
		_world->CleanUpworld();
		break;
	case Level2:
		cout << " Level 2 destroyed " << endl;
		_world->CleanUpworld();
		break;
	default:
		break;
	}
}

void LevelManager::Build_menu()
{
	cout << " Menu Build " << endl;
}

void LevelManager::Build_level_hub()
{
	cout << " Build level hub " << endl;
}

void LevelManager::Build_level_1()
{
	cout << " Build level 1 " << endl;
//	Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube.obj");
//	Mesh* pistolMesh = Mesh::load(config::MGE_MODEL_PATH + "Flashlight.obj");
//	AbstractMaterial * normalMapMaterial = new TextureNormalMaterial(Texture::load(config::MGE_TEXTURE_PATH + ("Flashlight_diffuse.jpg")), glm::vec3(0.4f), 32.f, Texture::load(config::MGE_TEXTURE_PATH + "Flashlight_normal.jpg"));
//
//
//	Camera* camera = new Camera("camera", glm::vec3(0, 0, 0));
//	_world->add(camera);
//	_world->setMainCamera(camera);
//
//	GameObject * cubeNormal = new GameObject("normalmap", glm::vec3(0, 2, 0));
//	cubeNormal->setMesh(pistolMesh);
//	cubeNormal->setMaterial(normalMapMaterial);
//	//	cubeNormal->scale(glm::vec3(0.1f));
//	_world->add(cubeNormal);
//	cout << "Col size of flashlight " << cubeNormal->getMesh()->GetColliderSize() << endl;
//
//	camera->setBehaviour(new Orbit(cubeNormal, 10.0f, 80.0f, 10.0f));
//
//	LUAManager::InitializeFile();
//
//
//#pragma region Lights
//	//Directional Light
//	Light *dirLight = new DirectionalLight("Directional Light", glm::vec3(10, 7, 10), glm::vec3(1, 0, 1), glm::vec3(.5f, .5f, .5f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(1, 1, 1));
//	//dirLight->setMesh(cubeMeshF);
//	dirLight->setMaterial(new ColorMaterial(dirLight->diffuse));
//	_world->add(dirLight);
//	dirLight->setBehaviour(new KeysBehaviour2());
//	//Points lights
//	Light *light = new PointLight("PointLight1", glm::vec3(2, 2, 0), glm::vec3(.1f), glm::vec3(Color::Green), glm::vec3(0.3f));
//	_world->add(light);
//
//	Light * light2 = new PointLight("PointLight2", glm::vec3(-7, 2, 0), glm::vec3(.1f), glm::vec3(1), glm::vec3(0.3f));
//	_world->add(light2);
//
//
//	_world->AddLight(dirLight);
//	_world->AddLight(light);
//	_world->AddLight(light2);
//#pragma endregion Lights
//
//	//}
//
//
//	GameObject * cX = new GameObject("compassX", glm::vec3(1, 0, 0));
//	cX->setMesh(cubeMeshF);
//	cX->setMaterial(new ColorMaterial(Color::Red));
//	cX->scale(glm::vec3(1.9, 0.1f, 0.1f));
//	_world->add(cX);
//
//	GameObject * cY = new GameObject("compassY", glm::vec3(0, 1, 0));
//	cY->setMesh(cubeMeshF);
//	cY->setMaterial(new ColorMaterial(Color::Green));
//	cY->scale(glm::vec3(0.1f, 1.9, 0.1f));
//	_world->add(cY);
//
//	GameObject * cZ = new GameObject("compassZ", glm::vec3(0, 0, 1));
//	cZ->setMesh(cubeMeshF);
//	cZ->setMaterial(new ColorMaterial(Color::Blue));
//	cZ->scale(glm::vec3(0.1f, 0.1f, 1.9));
//	_world->add(cZ);
}

void LevelManager::Build_level_2()
{
	cout << " Build level 2 " << endl;
}