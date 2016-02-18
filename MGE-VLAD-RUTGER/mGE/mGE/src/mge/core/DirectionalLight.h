#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <mge/core/GameObject.hpp>


class DirectionalLight : public GameObject
{
    public:
        DirectionalLight();
        virtual ~DirectionalLight();
        glm::vec3 direction;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    protected:
    private:
};

#endif // DIRECTIONALLIGHT_H
