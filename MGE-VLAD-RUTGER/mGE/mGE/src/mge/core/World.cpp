#include <cassert>
#include <algorithm>
#include <iostream>
#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/light/Light.h"

using namespace std;

World::World():GameObject("root"), _mainCamera(0),_lights()
{
	//ctor
	GameObject::_world = this;
}

void World::setMainCamera (Camera* pCamera) {
    if (pCamera != NULL) _mainCamera = pCamera;
}

void World::AddLight(Light* pLight){
    _lights.push_back(pLight);
}
int World::getLightCount() {
    return _lights.size();
}

Light* World::getLightAt(int pIndex) {
    return _lights[pIndex];
}
Camera* World::getMainCamera () {
    return _mainCamera;
}
void World::CleanUpworld()
{
	while (_children.size() > 0) {
		GameObject* child = _children[0];
		remove(child);
		delete child;
	}
}
void World::renderDebugInfo() {
    //walk through all meshes and debug their normals
    GameObject* gameObject;
    for (int i = 0; i < getChildCount(); i++) {
        gameObject = getChildAt(i);
        //oo wise it would be better to do gameObject->renderDebugInfo, but since this is only for debugging
        //it's sort of pasted on
        if (gameObject->getMaterial() && gameObject->getMesh()) {
            gameObject->getMesh()->renderDebugInfo(gameObject->getWorldTransform(), this);
        }
    }

}

void World::DrawDebugCube(glm::mat4& pModelMatrix, World* pWorld,const glm::vec3& min,const glm::vec3 max, glm::vec3 pColor)
{
    glUseProgram(0);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(pWorld->getMainCamera()->getProjection()));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(glm::inverse(pWorld->getMainCamera()->getWorldTransform()) * pModelMatrix));

    glBegin(GL_LINES);
        glColor3fv(glm::value_ptr(pColor));

        glm::vec3 A(min.x, min.y, min.z);
        glm::vec3 B(max.x, min.y,min.z);
        glm::vec3 C(max.x, min.y,max.z);
        glm::vec3 D(min.x, min.y,max.z);

        glm::vec3 E(min.x, max.y, min.z);
        glm::vec3 F(max.x, max.y,min.z);
        glm::vec3 G(max.x, max.y,max.z);
        glm::vec3 H(min.x, max.y,max.z);

        glVertex3fv(glm::value_ptr(A));
        glVertex3fv(glm::value_ptr(B));

        glVertex3fv(glm::value_ptr(B));
        glVertex3fv(glm::value_ptr(C));

        glVertex3fv(glm::value_ptr(C));
        glVertex3fv(glm::value_ptr(D));

        glVertex3fv(glm::value_ptr(D));
        glVertex3fv(glm::value_ptr(A));


        glVertex3fv(glm::value_ptr(A));
        glVertex3fv(glm::value_ptr(E));

        glVertex3fv(glm::value_ptr(B));
        glVertex3fv(glm::value_ptr(F));

        glVertex3fv(glm::value_ptr(C));
        glVertex3fv(glm::value_ptr(G));


        glVertex3fv(glm::value_ptr(E));
        glVertex3fv(glm::value_ptr(F));

        glVertex3fv(glm::value_ptr(F));
        glVertex3fv(glm::value_ptr(G));

        glVertex3fv(glm::value_ptr(G));
        glVertex3fv(glm::value_ptr(H));

        glVertex3fv(glm::value_ptr(H));
        glVertex3fv(glm::value_ptr(E));


    glEnd();

}

