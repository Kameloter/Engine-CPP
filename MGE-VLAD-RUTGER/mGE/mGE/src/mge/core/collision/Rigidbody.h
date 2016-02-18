#ifndef RIGIDBODY_H
#define RIGIDBODY_H


#include "glm.hpp"
#include "mge/core/GameObject.hpp"
class GameObject;
class Rigidbody
{
    public:
        Rigidbody(const glm::vec3 pVelocity, GameObject * pParent);
        virtual ~Rigidbody();
//        Rigidbody(const Rigidbody& other);

        void simulatePhysics(float pDelta);


        inline const glm::vec3 getPosition() const { return _position; }
        inline void setPosition (const glm::vec3 pPosition) { _position = pPosition;}


        inline const glm::vec3 getVelocity() const { return _velocity; }
        inline void setVelocity (const glm::vec3 pVelocity) { _velocity = pVelocity;}

        inline const bool getIsKinematic() const { return _isKinematic;}
        inline void setIsKinemati(const bool pIsKinematic) { _isKinematic = pIsKinematic;}

        GameObject* parent;
    protected:
    private:

        glm::vec3 _position;
        glm::vec3 _velocity;
        bool _isKinematic;


};

#endif // RIGIDBODY_H
