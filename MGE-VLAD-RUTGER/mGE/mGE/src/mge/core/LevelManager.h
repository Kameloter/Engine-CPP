#pragma once
#include <SFML\Graphics.hpp>
using namespace std;
enum GameLevels
{
	Idle,Menu, HUB, Level1, Level2
};

class PhysicsWorld;
class LevelManager
{
public:

	

    GameLevels currentlevel;


	LevelManager(PhysicsWorld * pWorld, sf::Window * pWindow);
	~LevelManager();
	void testUpdate();
	 
	 void SwitchToLevel(GameLevels pToLevel);
private:
	void BuildLevel(GameLevels pLevel);
	void DestroyLevel(GameLevels pLevel);

	void Build_menu();
	void Build_level_hub();
	void Build_level_1();
	void Build_level_2();


	PhysicsWorld * _world;
	sf::Window * _window;
};

