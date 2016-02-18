#include <glm.hpp>
#include "mge/behaviours/Orbit.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>


#include <iostream>
using namespace std;
float maxDistance;
Orbit::Orbit(GameObject * pTarget,float pRotationSpeed,float pMaxRotationX,float pDistance): AbstractBehaviour(),
 _target(pTarget),_rotationSpeed(pRotationSpeed),_distace(pDistance),_maxRotationX(pMaxRotationX)
{
    maxDistance = pDistance;
}

Orbit::~Orbit()
{
    //dtor
}

/**
 * Looks at the given target
 */
float lastMouseX;
float lastMouseY;
float mouseDeltaX;
float mouseDeltaY;
void Orbit::update( float step )
{
   // glm::vec3 fromAngle;
    float mouseX;
    float mouseY;
    mouseX = sf::Mouse::getPosition().x;
    mouseY = sf::Mouse::getPosition().y;
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        mouseDeltaX = mouseX - lastMouseX;
        mouseDeltaY = mouseY - lastMouseY;

    }else{
      //  fromAngle = _owner->getLocalPosition();
        mouseDeltaX *= 0.9f;
        mouseDeltaY *= 0.9f;
    }

    lastMouseX = mouseX;
    lastMouseY = mouseY;

    glm::vec2 mouseDelta(mouseDeltaX,mouseDeltaY);
    mouseDelta *= 0.001f;
    mouseDelta *= _rotationSpeed;

    glm::mat4 camTrans = _owner->getTransform();


    if(sf::Mouse::isButtonPressed(sf::Mouse::XButton1)){
        _distace += 0.1f;
       // cout<<"press"<<endl;
    }else if(sf::Mouse::isButtonPressed(sf::Mouse::XButton2)){
    //    cout<<"press"<<endl;
        _distace -= 0.1f;
    }
    if(_distace<1.5f)
        _distace=1.5f;
    else if(_distace>maxDistance)
            _distace =maxDistance;


    camTrans = glm::translate(camTrans, glm::vec3(mouseDelta.x ,mouseDelta.y ,0));
    glm::vec3 delta = glm::normalize(glm::vec3(camTrans[3]) - _target->getLocalPosition() ) * _distace;
     //   std::cout<< glm::length(delta) << " <---- Delta" << std::endl;

   camTrans[3] = glm::vec4(_target->getLocalPosition() + delta,1);
    //glm::vec3 tarpos = _target->getLocalPosition();

    float angle = glm::degrees(glm::angle(delta,glm::vec3(delta.x,0,delta.z)));
    //float angle2 = glm::degrees(glm::angle(delta,fromAngle));


//    std::cout<< angle << " <---- ANGLE !  " << angle2 << " <---- ANGLE2 !" << std::endl;
    if(angle > _maxRotationX) return;

    _owner->setTransform(
        glm::inverse (
            glm::lookAt (glm::vec3(camTrans[3]), _target->getLocalPosition(), glm::vec3(0,1,0))
        )
    );


    //manually
    //the other way then you would expect, the camera is flipped over the z axis we are staring out of its a.. basically ;)
    //this is due to how the perspective matrix is set up
//    glm::vec3 forward = glm::normalize(_owner->getLocalPosition() - _target->getLocalPosition());
//    glm::vec3 right = glm::cross (glm::vec3(0,1,0), forward);
//    glm::vec3 up = glm::cross (forward, right);
//
//    _owner->setTransform(
//      glm::mat4 (glm::vec4(right,0), glm::vec4(up,0), glm::vec4(forward,0), glm::vec4(_owner->getLocalPosition(),1) )
//    );
}
