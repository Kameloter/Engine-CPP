#include "LUAManager.h"


#include <iostream>
#include <string>
using namespace std;
#include <sstream>
#include <iostream>

lua_State * lua;

LUAManager::LUAManager()
{

    //ctor
}

LUAManager::~LUAManager()
{
    //dtor
}

int LUAManager::InitializeFile(){

   // cout<<"working lua"<<endl;
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
