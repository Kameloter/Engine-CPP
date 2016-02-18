#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "mge/core/light/Light.h"


class DirectionalLight : public Light
{
    public:
        DirectionalLight(std::string pName = "DirLight", glm::vec3 pPosition = glm::vec3(), glm::vec3 pDirection = glm::vec3(),glm::vec3 pAmbient= glm::vec3(),glm::vec3 pDiffuse= glm::vec3(), glm::vec3 pSpecular= glm::vec3());
        virtual ~DirectionalLight();

        glm::vec3 direction;




    protected:
    private:
};

#endif // DIRECTIONALLIGHT_H
