#include "Rigidbody.h"
#define gravity 2.5
#include "mge/core/GameObject.hpp"
Rigidbody:: Rigidbody(const glm::vec3 pVelocity, GameObject* pParent):
    _position(pParent->getLocalPosition()),
    _velocity(pVelocity),
    parent(pParent),
    _isKinematic(false)
{

}
//Rigidbody::Rigidbody(const Rigidbody& other) :
//    _position(other._position),
//    _velocity(other._velocity)
//{
//
//}
Rigidbody::~Rigidbody()
{
    //dtor
}


void Rigidbody::simulatePhysics(float pDelta)
{
    if(!_isKinematic)
    {
        _velocity += glm::vec3(0, -gravity, 0);
      //   std::cout << "Vel lenght " << glm::length(_velocity )<< std::endl;
        if(glm::length(_velocity) <= .1f)
        {
            _velocity = glm::vec3(0);
            std::cout << "Velocity zeroed " << _velocity << std::endl;
        }
    }else
    {
        _velocity = glm::vec3(0);
        std::cout << "Velocity zeroed " << _velocity << std::endl;
    }


    _position += _velocity * pDelta;


    if(parent != NULL) parent->setLocalPosition(_position);

}


