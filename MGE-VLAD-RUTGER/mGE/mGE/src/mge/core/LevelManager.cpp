//World , components , managers
#include "LevelManager.h"
#include "mge/core/collision/PhysicsWorld.h"
#include "mge/core/Mesh.hpp"
#include "mge/LUA/LUAManager.h"
#include "mge/core/Camera.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/xml/XmlReader.h"

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
#include "mge/behaviours/StatueBehaviour.h"
#include "mge/behaviours/PressurePlateBehaviour.h"
#include "mge/behaviours/CollectableBehaviour.h"
#include "mge/behaviours/FPCamera.h"
#include "mge/behaviours/LookAt.hpp"
#include "mge/behaviours/Orbit.hpp"

//Util
#include "mge/util/Color.h"
#include "mge/config.hpp"

LevelManager::LevelManager(PhysicsWorld * pWorld, sf::Window * pWindow):
	_world(pWorld)
{
	_window = pWindow;
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
	AbstractMaterial * colorMat = new ColorMaterial(Color::Pink);

	Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube.obj");

	Camera* camera = new Camera("camera", glm::vec3(0, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);

	RigidbodyGameObject * Player = new RigidbodyGameObject("Player", glm::vec3(4, 1.5, 4), _world);
	Player->AddBoxCollider(1, 1, 1);
	Player->setMesh(cubeMeshF);
	Player->setMaterial(colorMat);
	Player->setBehaviour(new FPController(50.0f, 1.0f, camera, FPController::InputType::WASD));
	_world->add(Player);

	camera->setParent(Player);
	camera->setLocalPosition(glm::vec3(0, 2, 0));
	camera->setBehaviour(new FPCamera(1.0f, 1.0f, Player, _window));

	
	GameObject * collectable = new GameObject("collectable", glm::vec3(8, 1.5, 15));
	collectable->setMesh(cubeMeshF);
	collectable->setMaterial(colorMat);
	collectable->setBehaviour(new CollectableBehaviour());
	_world->add(collectable);

	RigidbodyGameObject * statue = new RigidbodyGameObject("statue", glm::vec3(8, 1.5, 4), _world);
	statue->AddBoxCollider(1, 1, 1);
	statue->setMesh(cubeMeshF);
	statue->scale(glm::vec3(1, 4, 1));
	statue->setMaterial(colorMat);
	statue->setBehaviour(new StatueBehaviour());
	_world->add(statue);

	StaticGameObject * plate = new StaticGameObject("plate", glm::vec3(8, 1.5, 2), _world);
	//plate->AddBoxCollider(1, 1, 1);
	plate->setMesh(cubeMeshF);
	plate->setMaterial(colorMat);
	plate->setBehaviour(new PressurePlateBehaviour());
	_world->add(plate);


	RigidbodyGameObject * Door = new RigidbodyGameObject("door", glm::vec3(8, 1.5, 10), _world);
	Door->AddBoxCollider(1, 1, 1);
	Door->setMesh(cubeMeshF);
	Door->setMaterial(colorMat);
	Door->setBehaviour(new DoorBehaviour());
	dynamic_cast<DoorBehaviour*>(Door->getBehaviour())->InitializePositions(glm::vec3(0, 5, 0));
	_world->add(Door);

	dynamic_cast<CollectableBehaviour*>(collectable->getBehaviour())->SetPlayer(Player);
	dynamic_cast<StatueBehaviour*>(statue->getBehaviour())->SetPlayer(Player);
	dynamic_cast<PressurePlateBehaviour*>(plate->getBehaviour())->SetStatue(statue);
	dynamic_cast<DoorBehaviour*>(Door->getBehaviour())->AddPressurePlate(plate);

	XmlReader * xmlReader;
	xmlReader = new XmlReader();
	xmlReader->SetupLevelGeometry(_world);

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