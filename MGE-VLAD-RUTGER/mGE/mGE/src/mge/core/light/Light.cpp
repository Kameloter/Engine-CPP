#include "Light.h"

Light::Light(std::string pName, glm::vec3 pPosition, glm::vec3 pAmbient, glm::vec3 pDiffuse, glm::vec3 pSpecular) :
    GameObject(pName,pPosition), ambient(pAmbient), diffuse(pDiffuse), specular(pSpecular)
{
    //ctor
}

Light::~Light()
{
    //dtor
}

