#include "LUAManager.h"


#include <iostream>
#include <string>
using namespace std;
#include <sstream>
#include <iostream>

//behaviours for objects
#include "mge/behaviours/StatueBehaviour.h"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/FPController.h"
#include "mge/behaviours/BoxBehaviour.h"
#include "mge/behaviours/DoorBehaviour.h"
#include "mge/behaviours/TriggerBehaviour.h"
#include "mge/behaviours/FPCamera.h"
#include "mge/behaviours/CollectableBehaviour.h"
#include "mge/behaviours/PressurePlateBehaviour.h"
#include "mge/behaviours/PushBlockBehaviour.h"
#include "mge/behaviours/SpikeBehaviour.h"
#include "mge/behaviours/GhostBehaviour.h"


#include "mge/core/collision/TriggerManager.h"


lua_State * lua;



std::vector<RigidbodyGameObject *> LUAManager::rigidObjects;
std::vector<StaticGameObject *> LUAManager::staticObjects;
std::vector<GameObject*> LUAManager::staticTriggerObjects;

LUAManager::LUAManager()
{

    //ctor
}

LUAManager::~LUAManager()
{
    //dtor
}

int LUAManager::InitializeFile(PhysicsWorld * pWorld){

	setObjects(pWorld->getStaticObjects(), pWorld->getRigidObjects(),pWorld->_triggerManager->getStaticTriggerObjects());
    lua = luaL_newstate();
    luaL_openlibs(lua);

	lua_pushcfunction(lua, ConnectStatueToPlate);
	lua_setglobal(lua, "ConnectStatueToPlate");
	lua_pushcfunction(lua, AddPressurePlateToDoor);
	lua_setglobal(lua, "AddPressurePlateToDoor");
	lua_pushcfunction(lua, SetOpenVector);
	lua_setglobal(lua, "SetOpenVector");
	lua_pushcfunction(lua, AddPressurePlateToBlock);
	lua_setglobal(lua, "AddPressurePlateToBlock");
	lua_pushcfunction(lua, SetOpenVectorBlock);
	lua_setglobal(lua, "SetOpenVectorBlock");
	lua_pushcfunction(lua, SetOpenVectorSpike);
	lua_setglobal(lua, "SetOpenVectorSpike");
	lua_pushcfunction(lua, SetKeyNeededDoor);
	lua_setglobal(lua, "SetKeyNeededDoor");
	lua_pushcfunction(lua, SetBeginEndGhost);
	lua_setglobal(lua, "SetBeginEndGhost");

    if (luaL_loadfile(lua, "assets/mge/lua/Room1.lua") || lua_pcall(lua, 0, 0, 0)) {
        printf("error: %s", lua_tostring(lua, -1));
        return -1;
    }

    lua_getglobal(lua, "Start");
//    if(!lua_isfunction(lua,-1)){
//        lua_pop(lua,1);
//        return -1;
//    }

    if (lua_pcall(lua, 0, 0, 0) != 0) {
        printf("error running function `Start': %s\n",lua_tostring(lua, -1));
    }
    lua_close(lua);
    return 0;
}

int LUAManager::CreateCube(lua_State * L){
   
    return 0;
}

int LUAManager::ConnectStatueToPlate(lua_State * L)
{
	string plateName = lua_tostring(L, 1);
	string statueName = lua_tostring(L, 2);

	StaticGameObject * plate = FindStaticTriggerObject(plateName);
	RigidbodyGameObject * statue = FindRigidObject(statueName);

	std::cout << plate->getName() << " + " << statue->getName() << std::endl;

	dynamic_cast<PressurePlateBehaviour*>(plate->getBehaviour())->SetStatue(statue);
	return 0;
}

int LUAManager::SetOpenVector(lua_State * L)
{
	string doorName = lua_tostring(L, 1);
	glm::vec3 translate = glm::vec3(lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4));

	StaticGameObject * door = FindStaticObject(doorName);
	dynamic_cast<DoorBehaviour*>(door->getBehaviour())->SetOpenPos(translate);
	return 0;
}

int LUAManager::SetOpenVectorBlock(lua_State * L)
{
	string blockName = lua_tostring(L, 1);
	glm::vec3 translate = glm::vec3(lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4));

	StaticGameObject * door = FindStaticObject(blockName);
	dynamic_cast<PushBlockBehaviour*>(door->getBehaviour())->SetOpenPos(translate);
	return 0;
}

int LUAManager::SetOpenVectorSpike(lua_State * L)
{
	string spikeName = lua_tostring(L, 1);
	glm::vec3 translate = glm::vec3(lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4));

	StaticGameObject * door = FindStaticTriggerObject(spikeName);
	dynamic_cast<SpikeBehaviour*>(door->getBehaviour())->SetOpenPos(translate);
	return 0;
}

int LUAManager::AddPressurePlateToDoor(lua_State * L)
{
	string doorName = lua_tostring(L, 1);
	string plateName = lua_tostring(L, 2);

	StaticGameObject * door = FindStaticObject(doorName);
	StaticGameObject * plate = FindStaticTriggerObject(plateName);

	dynamic_cast<DoorBehaviour*>(door->getBehaviour())->AddPressurePlate(plate);

	return 0;
}
int LUAManager::AddPressurePlateToBlock(lua_State * L)
{
	string blockName = lua_tostring(L, 1);
	string plateName = lua_tostring(L, 2);

	StaticGameObject * door = FindStaticObject(blockName);
	StaticGameObject * plate = FindStaticTriggerObject(plateName);

	dynamic_cast<PushBlockBehaviour*>(door->getBehaviour())->AddPressurePlate(plate);

	return 0;
}

int LUAManager::SetKeyNeededDoor(lua_State * L)
{
	std::cout << "jawhole" << std::endl;
	string doorName = lua_tostring(L, 1);
	int amount = lua_tonumber(L, 2);
	StaticGameObject * door = FindStaticObject(doorName);
	dynamic_cast<DoorBehaviour*>(door->getBehaviour())->SetKeysNeeded(amount);
	return 0;
}

int LUAManager::SetBeginEndGhost(lua_State * L)
{
	string ghostName = lua_tostring(L, 1);
	glm::vec3 openPos = glm::vec3(lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4));
	glm::vec3 closedPos = glm::vec3(lua_tonumber(L, 5), lua_tonumber(L, 6), lua_tonumber(L, 7));

	StaticGameObject * ghost = FindStaticTriggerObject(ghostName);
	std::cout << ghost->getName() << openPos << closedPos << std::endl;

	dynamic_cast<GhostBehaviour*>(ghost->getBehaviour())->setBeginEnd(openPos,closedPos);
	return 0;
}

void LUAManager::setObjects(std::vector<StaticGameObject*> pStaticObjects, std::vector<RigidbodyGameObject*> pRigidObjects, std::vector<GameObject*> pTriggerStatic)
{
	rigidObjects = pRigidObjects;
	staticObjects = pStaticObjects;
	staticTriggerObjects = pTriggerStatic;
}

RigidbodyGameObject * LUAManager::FindRigidObject(std::string name) {
	for (int i = 0; i<rigidObjects.size(); i++) {
		if (rigidObjects[i]->getName() == name) {
			return rigidObjects[i];
		}
	}
}

StaticGameObject * LUAManager::FindStaticObject(std::string name)
{
	for (int i = 0; i<staticObjects.size(); i++) {
		//std::cout << name << " + " << staticObjects[i]->getName() << std::endl;
		if (staticObjects[i]->getName() == name) {
	
			return staticObjects[i];
		}
	}
	std::cout << "No such item found" << std::endl;
}

StaticGameObject * LUAManager::FindStaticTriggerObject(std::string name)
{	
	for (int i = 0; i < staticTriggerObjects.size(); i++) {
		//std::cout << name << " + " << staticTriggerObjects[i]->getName() << std::endl;
		if (staticTriggerObjects[i]->getName() == name) {
			return dynamic_cast<StaticGameObject*>(staticTriggerObjects[i]);
		}
	}
	std::cout << "No such item found" << std::endl;
}
