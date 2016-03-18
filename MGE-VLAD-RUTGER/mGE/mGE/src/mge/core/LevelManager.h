#pragma once
#include <SFML\Graphics.hpp>
using namespace std;
enum GameLevels
{
	Idle,Menu, HUB, HUBTUTORIAL, Level1, Level2, Level3, Level4
};

class PhysicsWorld;
//class XmlReader;
class DebugHud;
class LevelManager
{
public:

	static LevelManager& getInstance() {
		static LevelManager  _instance;

		return _instance;
	}

   GameLevels currentlevel;
	LevelManager();
	~LevelManager();

	void testUpdate();

	void setWorldWindow(PhysicsWorld * pWorld, sf::Window * pWindow, DebugHud * hud);
	 
	 void SwitchToLevel(GameLevels pToLevel);

	 void ReloadLevel();
private:
	void BuildLevel(GameLevels pLevel);
	void DestroyLevel(GameLevels pLevel);

	void Build_menu();
	void Build_level_hub();
	void Build_level_hub_tutorial();
	void Build_level_1();
	void Build_level_2();
	void Build_level_3();
	void Build_level_4();

	PhysicsWorld * _world;
	sf::Window * _window;
	DebugHud * _hud;
	
	static LevelManager * _instance;
};

