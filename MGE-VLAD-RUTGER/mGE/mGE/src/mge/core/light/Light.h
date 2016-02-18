#ifndef LIGHT_H
#define LIGHT_H

#include <mge/core/GameObject.hpp>


class Light : public GameObject
{


    public:
         enum LightType{Directional,Point,Spot
        };
        Light(std::string pName, glm::vec3 pPosition, glm::vec3 pAmbient, glm::vec3 pDiffuse, glm::vec3 pSpecular);
        virtual ~Light();
        LightType type;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    protected:
    private:
};

#endif // LIGHT_H
