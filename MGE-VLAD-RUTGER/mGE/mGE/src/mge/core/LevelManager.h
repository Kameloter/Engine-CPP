#pragma once
using namespace std;
enum GameLevels
{
	Idle,Menu, HUB, Level1, Level2
};

class World;
class LevelManager
{
public:

	

    GameLevels currentlevel;


	LevelManager(World * pWorld);
	~LevelManager();
	
	 
	 void SwitchToLevel(GameLevels pToLevel);
private:
	void BuildLevel(GameLevels pLevel);
	void DestroyLevel(GameLevels pLevel);

	void Build_menu();
	void Build_level_hub();
	void Build_level_1();
	void Build_level_2();


	World * _world;
};

