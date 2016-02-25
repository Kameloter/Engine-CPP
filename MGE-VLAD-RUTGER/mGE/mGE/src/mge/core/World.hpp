#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "mge/core/GameObject.hpp"

class Light;
class Camera;

class World : public GameObject
{
	public:
        World();

		void setMainCamera (Camera* pCamera);
		Camera* getMainCamera();

        void renderDebugInfo();
        void DrawDebugCube(glm::mat4& pModelMatrix, World* pWorld,const glm::vec3& min,const glm::vec3 max, glm::vec3 pColor);
        void AddLight(Light* pLight);
        const std::vector<Light*>& GetLights(){return _lights;};
        int getLightCount();
        Light* getLightAt(int pIndex);
		

    protected:
        std::vector<Light*> _lights;
		virtual void CleanUpworld();
	private:
	    Camera* _mainCamera;

};


#endif // WORLD_H
