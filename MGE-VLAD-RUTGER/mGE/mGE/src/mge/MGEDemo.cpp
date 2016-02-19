//#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;
#include "mge/core/Renderer.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/xml/XmlReader.h"
#include "mge/core/collision/PhysicsWorld.h"
#include "mge/core/FPS.hpp"
#include "mge/LUA/LUAManager.h"
#include "mge/core/Camera.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/core/collision/Rigidbody.h"
#include "mge/core/collision/RigidbodyGameObject.h"
#include "mge/core/collision/StaticGameObject.h"
#include "mge/core/light/Light.h"
#include "mge/core/light/DirectionalLight.h"
#include "mge/core/light/PointLight.h"
#include "mge/core/light/SpotLight.h"
#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TerrainMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/VertexLitColorMaterial.hpp"
#include "mge/materials/FragLitColorMaterial.hpp"
#include "mge/materials/PointLightMaterial.hpp"
#include "mge/materials/PointLightAttenuationMaterial.hpp"
#include "mge/materials/TextureLitMaterial.hpp"
#include "mge/materials/WobblyMaterial.hpp"
#include "mge/materials/TextureNormalMaterial.hpp"
#include "mge/materials/SpotLightMaterial.hpp"

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
#include "mge/util/Color.h"

//collision
#include "mge/core/collision/Collider.h"
#include "mge/core/collision/BoxCollider.h"
#include "mge/core/collision/SphereCollider.h"
#include "mge/core/collision/Collision.h"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/MGEDemo.hpp"

XmlReader * xmlReader;
//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo():AbstractGame ()
{
}

void MGEDemo::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

AbstractMaterial* pointLightMaterial;
AbstractMaterial* pointAttenuationMat;
PointLight* light2;
 RigidbodyGameObject* Player ;
GameObject* box;
void MGEDemo::_initializeScene()
{
    _renderer->setClearColor(0,0,0);

 //===============================  M E S H E S ====================================================================================================================================================//

    Mesh* planeQuad = Mesh::load (config::MGE_MODEL_PATH+"NormalPlane.obj");
    Mesh* cubeMeshF = Mesh::load (config::MGE_MODEL_PATH+"cube.obj");
//=====================================================================================================================================================================================================//
	

   //===============================  M A T E R I A L S ====================================================================================================================================================//
    AbstractMaterial * spotLightMaterial = new SpotLightMaterial(Color::Red);

    //MATERIALS

    //Texture Material + Light !
    AbstractMaterial* wallMat = new TextureLitMaterial(Texture::load (config::MGE_TEXTURE_PATH+"test.jpg"),32.f);

    AbstractMaterial* pillarMat = new TextureLitMaterial(Texture::load (config::MGE_TEXTURE_PATH+"pillar.jpg"),32.f);
    //Simple Texture material - No light
    AbstractMaterial* textureMaterial = new TextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+"land.jpg"));

    AbstractMaterial* terrainMaterial = new TerrainMaterial (Texture::load (config::MGE_TEXTURE_PATH+"diffuse1.jpg"),
                                                             Texture::load (config::MGE_TEXTURE_PATH+"water.jpg"),
                                                             Texture::load (config::MGE_TEXTURE_PATH+"diffuse3.jpg"),
                                                             Texture::load (config::MGE_TEXTURE_PATH+"diffuse4.jpg"),
                                                             Texture::load (config::MGE_TEXTURE_PATH+"splatmap.png"),
                                                             Texture::load (config::MGE_TEXTURE_PATH+"heightmap.png"));
    AbstractMaterial* textureMaterial2 = new TextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+"bricks.jpg"));

    AbstractMaterial * blueMaterial = new ColorMaterial(glm::vec3(0,0,1));
    AbstractMaterial * redMaterial = new ColorMaterial(glm::vec3(1,0,0));
    AbstractMaterial * greenMaterial = new ColorMaterial(glm::vec3(0,1,0));
    AbstractMaterial * maroonMaterial = new ColorMaterial(Color::Maroon);

 //==========================================================================================================================================================================================================================//

    DoorBehaviour * doorBehaviour = new DoorBehaviour();



/** PLAYER AND CAMERA
*/

    Camera* camera = new Camera ("camera", glm::vec3(0,0,0));
    _world->add(camera);
    _world->setMainCamera(camera);

    Player = new RigidbodyGameObject("Player", glm::vec3(4,1.5,4),_world);
	Player->AddBoxCollider(1, 1, 1);
    Player->setMesh(cubeMeshF);
    Player->setMaterial(maroonMaterial);
   // Player->setBehaviour(new FPController(10.0f,1.0f,camera,FPController::InputType::WASD));
    _world->add(Player);

    camera->setParent(Player);
    camera->setLocalPosition(glm::vec3(0,2,0));
   camera->setBehaviour(new FPCamera(1.0f,1.0f,Player,_window));
	//camera->setBehaviour(new Orbit(Player, 10.0f, 80.0f, 10.0f));


    //{ LIGHTS
    //Directional Light
    Light *dirLight = new DirectionalLight("Directional Light", glm::vec3(10,7,10),glm::vec3(1,0,1),glm::vec3(.5f,.5f,.5f),glm::vec3(1.f,1.f,1.f),glm::vec3(1,1,1));

    //Points lights
    Light *light = new PointLight("PointLight1", glm::vec3(2,2,0),glm::vec3(.1f),glm::vec3(Color::Green),glm::vec3(0.3f));
    _world->add(light);

    light2 = new PointLight("PointLight2", glm::vec3(-7,2,0),glm::vec3(.1f),glm::vec3(1),glm::vec3(0.3f));
    _world->add(light2);

    Light *light3 = new SpotLight("SpotLight",glm::vec3(0,-1,0),glm::vec3(.1f),glm::vec3(Color::Red),glm::vec3(.5f));
    _world->add(light3);
    //}


    //ADD OBJECTS TO WORLD ! ================================================================
    //Add Lights
//    _world->AddLight(dirLight);
    _world->AddLight(light);
    _world->AddLight(light2);
    _world->AddLight(light3);
   // _world->AddLight(light4);
    //======================================================================================
    //PHYSICS TESTS

   xmlReader = new XmlReader();
   xmlReader->SetupLevelGeometry(_world);

    LUAManager::InitializeFile();
}

bool won = false;
void MGEDemo::_render() {
	if (Player->getLocalPosition().x > 4.5f) won = true;
	if (won) {
		string winText = " YOU WIN YAAY !";
		_hud->setWinTextInfo(winText);
	}

	AbstractGame::_render();
	_updateHud();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) system("cls");
}

void MGEDemo::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string(FPS::getFPS())+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}


MGEDemo::~MGEDemo()
{
	//dtor
}
