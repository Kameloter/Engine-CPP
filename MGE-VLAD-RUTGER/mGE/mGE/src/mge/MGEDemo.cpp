#include <iostream>
#include <string>
using namespace std;
#include "mge/core/Renderer.hpp"
#include "mge/core/World.hpp"
#include "mge/core/FPS.hpp"
#include "mge/core/collision/PhysicsWorld.h"
#include "mge/core/LevelManager.h"
#include "mge/UI/MainMenu.h"

#include "mge/StatsHolder.h"

//
////collision
//#include "mge/core/collision/Collider.h"
//#include "mge/core/collision/BoxCollider.h"
//#include "mge/core/collision/SphereCollider.h"
//#include "mge/core/collision/Collision.h"
#include "mge/core/Timer.hpp"
#include "mge/util/DebugHud.hpp"
#include "mge/SubtitleManager.h"
#include "mge/MGEDemo.hpp"


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

LevelManager * levelManager;
MainMenu * mainMenu;
void MGEDemo::_initializeScene()
{
	_renderer->setClearColor(0, 0, 0);
	levelManager = new LevelManager(_world,_window);
	levelManager->SwitchToLevel(GameLevels::Menu);
	mainMenu = new MainMenu(_window);

	


	

	//GameObject * cubeNormal = new GameObject("normalmap", glm::vec3(0, 2, 0));
	//cubeNormal->setMesh(cubeMeshF);
	//cubeNormal->setMaterial(normalMapMaterial2);
	////	cubeNormal->scale(glm::vec3(0.1f));
	//_world->add(cubeNormal);



	SubtitleManager::addSubtitle("Trigger1", "yoo maaan , this gas is so so dengruruuus");
	SubtitleManager::addSubtitle("Trigger1", "yoo maaan , this gas is so so dengruruuus");
	SubtitleManager::addSubtitle("Trigger2", "yoo maaan , this gas is so so dengruruuus");



	

}

bool press = false;
void MGEDemo::_render() {

	//_world->renderDebugInfo();
	AbstractGame::_render();
	_updateHud();
	if (levelManager->currentlevel == GameLevels::Menu)
	{
		
		if (mainMenu->ButtonPressed(_window->getSize().x / 2 ,_window->getSize().y / 2, " START GAME !"))
		{
			levelManager->SwitchToLevel(GameLevels::HUB);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && !press)
	{
		press = true;
		std::cout << " press " << std::endl;
		SubtitleManager::playSubtitle("Trigger1", 5.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) levelManager->SwitchToLevel(GameLevels::Menu);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) levelManager->SwitchToLevel(GameLevels::HUB);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) levelManager->SwitchToLevel(GameLevels::Level1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) levelManager->SwitchToLevel(GameLevels::Level2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) _world->CleanUpPhysicsWorld();

	levelManager->testUpdate();

}

void MGEDemo::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string(FPS::getFPS())+"\n";
	SubtitleManager::update(Timer::deltaTime());
	SubtitleManager::draw(_window);

    _hud->setDebugInfo(debugInfo);
	_hud->setWinTextInfo("Score : " + std::to_string(StatsHolder::getScore()));
    _hud->draw();
}


MGEDemo::~MGEDemo()
{
	//dtor
}
