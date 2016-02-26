#ifndef LUAMANAGER_H
#define LUAMANAGER_H


#include "lua.hpp"
#include "lauxlib.h"
#include "lualib.h"
#include "mge/core/collision//PhysicsWorld.h"

#include "mge/core/collision/RigidbodyGameObject.h"
#include "mge/core/collision/StaticGameObject.h"

#include <vector>

class LUAManager
{
    public:
        static lua_State * L;
      //  static void InitializeRoomFile();
        static int InitializeFile(PhysicsWorld *pWorld);
        static int CreateCube(lua_State * L);
		static int ConnectStatueToPlate(lua_State * L);
		static int SetOpenVector(lua_State * L);
		static int AddPressurePlateToDoor(lua_State * L);


		static void setObjects(std::vector<StaticGameObject *> pStaticObjects, std::vector<RigidbodyGameObject *> pRigidObjects, std::vector<GameObject*> pTriggerStatic);

        LUAManager();
        virtual ~LUAManager();
    protected:
    private:
		static std::vector<RigidbodyGameObject *> rigidObjects;
		static std::vector<StaticGameObject *> staticObjects;
		static std::vector<GameObject*> staticTriggerObjects;
		static RigidbodyGameObject * FindRigidObject(std::string name);
		static StaticGameObject * FindStaticObject(std::string name);
		static StaticGameObject * FindStaticTriggerObject(std::string name);
};

#endif // LUAMANAGER_H