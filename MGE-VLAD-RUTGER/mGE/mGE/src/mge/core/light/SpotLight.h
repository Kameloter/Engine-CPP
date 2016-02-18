#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "mge/core/light/Light.h"


class SpotLight : public Light
{
    public:
        SpotLight(std::string pName = "SpotLight", glm::vec3 pPosition = glm::vec3(),glm::vec3 pAmbient= glm::vec3(),glm::vec3 pDiffuse= glm::vec3(), glm::vec3 pSpecular= glm::vec3());
        virtual ~SpotLight();

        float quadratic;
        float constant;
        float linear;

    protected:
    private:
};

#endif // SPOTLIGHT_H
