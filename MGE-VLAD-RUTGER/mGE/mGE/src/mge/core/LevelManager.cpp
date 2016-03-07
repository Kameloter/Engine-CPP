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

LevelManager::LevelManager(PhysicsWorld * pWorld, sf::Window* pWindow) :
	_world(pWorld), _window(pWindow)
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
StaticGameObject * testtrig = nullptr;
void LevelManager::DestroyLevel(GameLevels pLevel)
{
	testtrig = nullptr;
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
		_world->CleanUpPhysicsWorld();
		break;
	case Level2:
		cout << " Level 2 destroyed " << endl;
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

void LevelManager::Build_level_hub()
{
	cout << " Build level hub " << endl;
}
sf::SoundBuffer ambientBuffer;
sf::Sound soundAmbient;
void LevelManager::Build_level_1()
{
	cout << " Build level 1 " << endl;

	/*XmlReader * xmlReader;
	xmlReader = new XmlReader(dynamic_cast<PhysicsWorld*>(_world));*/
//	xmlReader->SetupLevelGeometry(dynamic_cast<PhysicsWorld*>(_world));
	Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube.obj");
	Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");


//	Mesh* pistolMesh = Mesh::load(config::MGE_MODEL_PATH + "Flashlight.obj");
//	AbstractMaterial * normalMapMaterial = new TextureNormalMaterial(Texture::load(config::MGE_TEXTURE_PATH + ("Flashlight_diffuse.jpg")), glm::vec3(0.4f), 32.f, Texture::load(config::MGE_TEXTURE_PATH + "Flashlight_normal.jpg"));
	//AbstractMaterial * normalMapMaterial2 = new TextureNormalMaterial(Texture::load(config::MGE_TEXTURE_PATH + ("rocks.jpg")), glm::vec3(0.4f), 32.f, Texture::load(config::MGE_TEXTURE_PATH + "rocksnormal.png"));
//	AbstractMaterial * normalMapMaterial3 = new TextureNormalMaterial(Texture::load(config::MGE_TEXTURE_PATH + ("planeDiff.png")), glm::vec3(1), 1 , Texture::load(config::MGE_TEXTURE_PATH + "planeNormal.png"));
//	AbstractMaterial * combinedMat = new TextureLitMaterial(Texture::load(config::MGE_TEXTURE_PATH + "planeDiff.png"), Texture::load(config::MGE_TEXTURE_PATH + "planeNormal.png"), 32.f);

	//Camera* camera = new Camera("camera", glm::vec3(0, 0, 0));
	//_world->add(camera);
	//_world->setMainCamera(camera);

	//Player * player = new Player("Player", glm::vec3(4, 1.5, 4), _world, camera);

	////RigidbodyGameObject * Player = new RigidbodyGameObject("Player", glm::vec3(4, 1.5, 4), _world);
	////glm::vec3 center = Player->getLocalPosition();
	////glm::vec3 minbound(center.x - 0.5f, center.y - 0.5f, center.z - 0.5f);
	////glm::vec3 maxbound(center.x + 0.5f, center.y + 0.5f, center.z + 0.5f);
	////Player->SetBounds(minbound, maxbound);
	////Player->AddBoxCollider(1, 1, 1);
	////Player->setMesh(cubeMeshF);
	////Player->setMaterial(new ColorMaterial(Color::Green));
	////Player->setBehaviour(new FPController(30.0f, 1.0f, camera, FPController::InputType::WASD));
	//_world->add(player);

	// camera->setParent(player);
	// camera->setLocalPosition(glm::vec3(0,2,0));
	// camera->setBehaviour(new FPCamera(1.0f,1.0f, player));

	 //testtrig = new StaticGameObject("obj6", glm::vec3(3, 1, 3), _world,true);

	 //glm::vec3 center2 = testtrig->getLocalPosition();
	 //glm::vec3 minbound2(center2.x - 0.5f, center2.y - 0.5f, center2.z - 0.5f);
	 //glm::vec3 maxbound2(center2.x + 0.5f, center2.y + 0.5f, center2.z + 0.5f);
	 //testtrig->SetBounds(minbound2, maxbound2);
	 //testtrig->AddBoxCollider(1, 1, 1);
	 //testtrig->setMesh(cubeMeshF);
	 //testtrig->setMaterial(new ColorMaterial(Color::Tomato));
	 //_world->add(testtrig);

	//GameObject * cubeNormal = new GameObject("normalmap", glm::vec3(0, 0, 0));
	//cubeNormal->setMesh(logMesh);
	//cubeNormal->setMaterial(logMat);
	//_world->add(cubeNormal);
	//camera->setBehaviour(new Orbit(cubeNormal, 10.0f, 80.0f, 10.0f));

//	LUAManager::InitializeFile();
	 //StaticGameObject * box = new StaticGameObject("box", glm::vec3(3, 1, 3), _world);
	 //box->setMesh(cubeMeshF);
	 //glm::vec3 colsize = box->getMesh()->GetColliderSize();
	 //box->AddBoxCollider(colsize.x, colsize.y, colsize.z);
	 //box->setMaterial(new ColorMaterial(Color::Blue));
	 //_world->add(box);
	 //box->setBehaviour(new StatueBehaviour());
	 //dynamic_cast<StatueBehaviour*>(box->getBehaviour())->SetPlayer(player);

#pragma region Lights
	//Directional Light
	Light *dirLight = new DirectionalLight("Directional Light", glm::vec3(0, 0, 0), glm::vec3(0, -1, 2), glm::vec3(0.3), glm::vec3(1), glm::vec3(1));
	//dirLight->setMesh(cubeMeshF);
	//dirLight->setMaterial(new ColorMaterial(dirLight->diffuse));
	//_world->add(dirLight);
	//dirLight->setBehaviour(new KeysBehaviour2());
	//Points lights
	Light *light = new PointLight("PointLight1", glm::vec3(40, 5, 35), glm::vec3(.3), glm::vec3(1,1,1), glm::vec3(0.1));
	//Light *light2 = new PointLight("PointLight1", glm::vec3(28, 5, 35), glm::vec3(.3), glm::vec3(1, 1, 1), glm::vec3(0.1));
	//Light *light3 = new PointLight("PointLight1", glm::vec3(28, 5, 25), glm::vec3(.3), glm::vec3(1, 1, 1), glm::vec3(0.1));
	//Light *light4 = new PointLight("PointLight1", glm::vec3(40, 5, 35), glm::vec3(.3), glm::vec3(1, 1, 1), glm::vec3(0.1));
	/*light->setMesh(cubeMeshF);
	light->setMaterial(new ColorMaterial(light->diffuse));
	light->scale(glm::vec3(0.1));
	_world->add(light);*/

	//light->setBehaviour(new KeysBehaviour2());


	_world->AddLight(dirLight);
	_world->AddLight(light);
	//_world->AddLight(light2);
	//_world->AddLight(light3);

#pragma endregion Lights

	XmlReader * xmlReader = new XmlReader(_world);
	xmlReader->LoadLevel("Level1");
	xmlReader->LoadInteractables("interactables");
	xmlReader->LoadSubtitleTriggers("subtitles");
	LUAManager::InitializeFile(_world); 

	
	if (!ambientBuffer.loadFromFile(config::MGE_SOUND_PATH + "ambience.wav"))
	{
		std::cout << " cant load sound " << std::endl;
	}
	soundAmbient.setBuffer(ambientBuffer);
	soundAmbient.setLoop(true);
	soundAmbient.play();
	//}

	/*RigidbodyGameObject * obj = new RigidbodyGameObject("obj", glm::vec3(1, 1, 0),_world);
	obj->setMesh(cubeMeshF);
	obj->setMaterial(normalMapMaterial2);
	_world->add(obj);

	RigidbodyGameObject * obj2 = new RigidbodyGameObject("obj2", glm::vec3(2, 1, 0), _world);
	obj2->setMesh(cubeMeshF);
	obj2->setMaterial(normalMapMaterial2);
	_world->add(obj2);

	RigidbodyGameObject * obj3 = new RigidbodyGameObject("obj3", glm::vec3(3, 1, 0), _world);
	obj3->setMesh(cubeMeshF);
	obj3->setMaterial(normalMapMaterial2);
	_world->add(obj3);

	StaticGameObject * obj4 = new StaticGameObject("obj4", glm::vec3(4, 1, 0), _world);
	obj4->setMesh(cubeMeshF);
	obj4->setMaterial(normalMapMaterial2);
	_world->add(obj4);

	StaticGameObject * obj5 = new StaticGameObject("obj5", glm::vec3(5, 1, 0), _world);
	obj5->setMesh(cubeMeshF);
	obj5->setMaterial(normalMapMaterial2);
	_world->add(obj5);

	StaticGameObject * obj6 = new StaticGameObject("obj6", glm::vec3(6, 1, 0), _world);
	obj6->setMesh(cubeMeshF);
	obj6->setMaterial(normalMapMaterial2);
	_world->add(obj6);

*/

	//GameObject * cX = new GameObject("compassX", glm::vec3(1, 0, 0));
	//cX->setMesh(cubeMeshF);
	//cX->setMaterial(new ColorMaterial(Color::Red));
	//cX->scale(glm::vec3(1.9, 0.1f, 0.1f));
	//_world->add(cX);

	//GameObject * cY = new GameObject("compassY", glm::vec3(0, 1, 0));
	//cY->setMesh(cubeMeshF);
	//cY->setMaterial(new ColorMaterial(Color::Green));
	//cY->scale(glm::vec3(0.1f, 1.9, 0.1f));
	//_world->add(cY);

	//GameObject * cZ = new GameObject("compassZ", glm::vec3(0, 0, 1));
	//cZ->setMesh(cubeMeshF);
	//cZ->setMaterial(new ColorMaterial(Color::Blue));
	//cZ->scale(glm::vec3(0.1f, 0.1f, 1.9));
	//_world->add(cZ);
}

void LevelManager::Build_level_2()
{
	cout << " Build level 2 " << endl;
}

void LevelManager::testUpdate()
{
	
}

