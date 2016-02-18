#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "mge/core/light/Light.h"


class PointLight : public Light
{
    public:
        PointLight(std::string pName = "PointLight", glm::vec3 pPosition = glm::vec3(),glm::vec3 pAmbient= glm::vec3(),glm::vec3 pDiffuse= glm::vec3(), glm::vec3 pSpecular= glm::vec3());
        virtual ~PointLight();

        float quadratic;
        float constant;
        float linear;

    protected:
    private:
};

#endif // POINTLIGHT_H
