#include <iostream>
#include <string>
using namespace std;
#include "mge/core/Renderer.hpp"
#include "mge/core/World.hpp"
#include "mge/core/FPS.hpp"
#include "mge/core/collision/PhysicsWorld.h"
#include "mge/core/LevelManager.h"
#include "mge/UI/MainMenu.h"
#include "mge/core/SoundManager.h"
#include "mge/StatsHolder.h"
#include "mge/core/FadeManager.h"
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
	LevelManager::getInstance().setWorldWindow(_world, _window);
	//levelManager = new LevelManager(_world,_window);
	LevelManager::getInstance().SwitchToLevel(GameLevels::Menu);
	mainMenu = new MainMenu(_window);

	


	

	//GameObject * cubeNormal = new GameObject("normalmap", glm::vec3(0, 2, 0));
	//cubeNormal->setMesh(cubeMeshF);
	//cubeNormal->setMaterial(normalMapMaterial2);
	////	cubeNormal->scale(glm::vec3(0.1f));
	//_world->add(cubeNormal);



	SubtitleManager::addSubtitle("Subtitles_01", "Maybe I can find something in here to open the door!",4.0f);	//4sec
	SubtitleManager::addSubtitle("Subtitles_02", "Hmm, a nice souvenir for at home!\n If I ever find the way out of here that is…",5.0f);	//5sec
	SubtitleManager::addSubtitle("Subtitles_03", "I’ll have to be careful here.. \nBut it seems like there should be a way across.",5.0f);//	5sec
	SubtitleManager::addSubtitle("Subtitles_04", "Nice..",3.0f);	//	3sec
	SubtitleManager::addSubtitle("Subtitles_05", "This room looks safe, and that object \nseems like it would fit perfectly in the big gate! \nI should take it with me.",8.0f);//	8sec
	SubtitleManager::addSubtitle("Subtitles_06", "Let’s hope this gate will take me out of here.",5.0f); //5 sec
	
	SubtitleManager::addSubtitle("HUB_01", "\"... I feel so dizzy, I should be glad i didn't break anything \nfrom that fall! Lets get back on my feet.\"", 8.0f);
	SubtitleManager::addSubtitle("Tutorial_01", "\"Use the keys W, A, S, D to move!\nUse mouse to look around !\"", 8.0f);
	SubtitleManager::addSubtitle("Tutorial_02", "\"Use the key SPACE to jump!\"", 8.0f);
	SubtitleManager::addSubtitle("HUB_02", "\"I need to get back to my team and continue finding\n the answer to the mayan prophecy that threatens our world!\"", 8.0f);
	SubtitleManager::addSubtitle("HUB_03", "\"But wait, this room seems very promising. \nI should explore a little and see what I can find.\"", 6.0f);
	SubtitleManager::addSubtitle("Tutorial_03", "\"'Ill better push that statue on the pressure plate\"", 8.0f);
	
	SubtitleManager::addSubtitle("HUB_04", "\"'CheckPoints Reached\"", 4.0f);
	SoundManager::getInstance().LoadSounds();
}

bool press = false;
void MGEDemo::_render() {

	//_world->renderDebugInfo();
	AbstractGame::_render();
	_updateHud();
	if (LevelManager::getInstance().currentlevel == GameLevels::Menu)
	{
		
		if (mainMenu->StartButtonPressed(_window->getSize().x / 2 ,_window->getSize().y / 2, " START GAME "))
		{
			LevelManager::getInstance().SwitchToLevel(GameLevels::HUBTUTORIAL);
		}

		/*if (mainMenu->ButtonPressed(_window->getSize().x / 2, (_window->getSize().y / 2) + 200, " QUIT GAME "))
		{
			_world->CleanUpPhysicsWorld();
			_window->close();
			_running = false;
		}*/
	}



	if (StatsHolder::PlayerDied == true)
	{
		StatsHolder::PlayerDied = false;
		LevelManager::getInstance().ReloadLevel();
	}

	levelManager->testUpdate();
	FadeManager::updateFadeScreen();
}

float lastUpdateTime = 0;

void MGEDemo::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string(FPS::getFPS())+"\n";
	SubtitleManager::update(Timer::deltaTime());
	SubtitleManager::draw(_window);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		FadeManager::setFade(false);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		FadeManager::setFade(true);
	}
    _hud->setDebugInfo(debugInfo);
	_hud->setWinTextInfo("Score : " + std::to_string(StatsHolder::getScore()));

	if (Timer::now() > lastUpdateTime + 0.1f)
	{
		_hud->setPerformanceDebugInfo("Render time: " + std::to_string((int)renderTime), "Update time: " + std::to_string((int)updateTime), "Triangle count:" + std::to_string(triangleCount), "Draw Calls:" + std::to_string(drawCalls));
		lastUpdateTime = Timer::now();
	}

    _hud->draw();
}


MGEDemo::~MGEDemo()
{
	//dtor
}
