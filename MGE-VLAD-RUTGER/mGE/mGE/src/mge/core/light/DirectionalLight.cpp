#include "DirectionalLight.h"

DirectionalLight:: DirectionalLight(std::string pName, glm::vec3 pPosition, glm::vec3 pDirection,glm::vec3 pAmbient,glm::vec3 pDiffuse, glm::vec3 pSpecular) :
                              Light(pName,pPosition,pAmbient,pDiffuse,pSpecular), direction(pDirection)
{
    type = LightType::Directional;
}

DirectionalLight::~DirectionalLight()
{
    //dtor
}
