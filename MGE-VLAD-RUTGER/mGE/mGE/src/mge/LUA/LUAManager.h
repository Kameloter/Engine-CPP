#ifndef LUAMANAGER_H
#define LUAMANAGER_H


#include "lua.hpp"
#include "lauxlib.h"
#include "lualib.h"
class LUAManager
{
    public:
        static lua_State * L;
      //  static void InitializeRoomFile();
        static int InitializeFile();
        static int CreateCube(lua_State * L);
        LUAManager();
        virtual ~LUAManager();
    protected:
    private:
};

#endif // LUAMANAGER_H
