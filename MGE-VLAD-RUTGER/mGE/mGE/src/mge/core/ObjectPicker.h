#ifndef OBJECTPICKER_H
#define OBJECTPICKER_H

#include <glm.hpp>
#include "mge/core/Camera.hpp"
#include <sfml/window/event.hpp>

class ObjectPicker
{
    public:
        ObjectPicker(Camera * pCamera , glm::mat4 pProjection, sf::Window * pWindow);
        virtual ~ObjectPicker();
        virtual void update( float step );

        glm::vec3 getCurrentRay();
    protected:
    private:
        glm::vec3 _currentRay;
        glm::mat4 _projectMatrix;
        glm::mat4 _viewMatrix;
        Camera * _camera;
        sf::Window *_window;

        glm::vec3 CalculateMouseRay();
        glm::vec2 GetNormalizedDeviceCoords(sf::Vector2i);
        glm::vec4 ToEyeCoords(glm::vec4 clipCoords);
        glm::vec3 ToWorldCoords(glm::vec4 eyeCoords);

};

#endif // OBJECTPICKER_H
