#include "ObjectPicker.h"
#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "mge/core/Camera.hpp"
#include <sfml/window/event.hpp>

#include <iostream>
using namespace std;

ObjectPicker::ObjectPicker(Camera * pCamera, glm::mat4 pProjection, sf::Window * pWindow)
{
    _camera = pCamera;
    _projectMatrix = pProjection;
    _viewMatrix = glm::inverse(pCamera->getWorldTransform());
    _window = pWindow;
}

ObjectPicker::~ObjectPicker()
{
    //dtor
}

void ObjectPicker::update( float step ){
  _viewMatrix =  glm::inverse(_camera->getWorldTransform());
  _currentRay = CalculateMouseRay();
  cout<<_currentRay<<endl;

}

glm::vec3 ObjectPicker::getCurrentRay(){
    return _currentRay;
}
glm::vec2 ObjectPicker::GetNormalizedDeviceCoords(sf::Vector2i mouseVector){
    float x = (2.0f * mouseVector.x) / _window->getSize().x - 1.0f;
    float y = (2.0f * mouseVector.y) / _window->getSize().y - 1.0f;

    return glm::vec2(x,y);
}

glm::vec4 ObjectPicker::ToEyeCoords(glm::vec4 clipCoords){
    glm::mat4 invertedProjection = glm::inverse(_projectMatrix);
    glm::vec4 eyeCoords = invertedProjection * clipCoords;
    return glm::vec4(eyeCoords.x , eyeCoords.y, -1.0f,0.0f);
}

glm::vec3 ObjectPicker::ToWorldCoords(glm::vec4 eyeCoords){
    glm::mat4 invertedView = glm::inverse(_viewMatrix);
    glm::vec4 rayWorld = invertedView * eyeCoords;
    glm::vec3 mouseRay = glm::vec3(rayWorld.x,rayWorld.y,rayWorld.z);
    glm::normalize(mouseRay);
    return mouseRay;
}

glm::vec3 ObjectPicker::CalculateMouseRay(){
    sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
    glm::vec2 normalizeMouseCoord = GetNormalizedDeviceCoords(mousePos);

    glm::vec4 clipCoords = glm::vec4(normalizeMouseCoord.x, normalizeMouseCoord.y,-1.0f,1.0f);
    glm::vec4 eyeCoord =  ToEyeCoords(clipCoords);
    glm::vec3 worldRay = ToWorldCoords(eyeCoord);

    return worldRay;
}


