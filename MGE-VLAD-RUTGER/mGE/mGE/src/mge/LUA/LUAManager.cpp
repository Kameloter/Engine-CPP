#include "LUAManager.h"


#include <iostream>
#include <string>
using namespace std;
#include <sstream>
#include <iostream>

lua_State * lua;



std::vector<RigidbodyGameObject *> LUAManager::rigidObjects;
std::vector<StaticGameObject *> LUAManager::staticObjects;

LUAManager::LUAManager()
{

    //ctor
}

LUAManager::~LUAManager()
{
    //dtor
}

int LUAManager::InitializeFile(PhysicsWorld * pWorld){

	setObjects(pWorld->getStaticObjects(), pWorld->getRigidObjects());
    cout<<"stat "<< staticObjects.size() << " rig " << rigidObjects.size() <<endl;
    lua = luaL_newstate();
    luaL_openlibs(lua);


    lua_pushcfunction(lua,CreateCube);
    lua_setglobal(lua, "CreateCube");

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
    std::cout<<"working???"<<std::endl;
    return 0;
}

void LUAManager::setObjects(std::vector<StaticGameObject*> pStaticObjects, std::vector<RigidbodyGameObject*> pRigidObjects)
{
	rigidObjects = pRigidObjects;
	staticObjects = pStaticObjects;
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
		if (staticObjects[i]->getName() == name) {
			return staticObjects[i];
		}
	}
}
