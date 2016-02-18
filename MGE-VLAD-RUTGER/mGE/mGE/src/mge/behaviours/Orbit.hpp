#ifndef Orbit_H
#define Orbit_H

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * Keeps the owner looking at the given target.
 */
class Orbit : public AbstractBehaviour
{
    public:
        Orbit (GameObject * pTarget, float pRotationSpeed, float pMaxRotationX,float pDistance);
        virtual ~Orbit();

        virtual void update( float step );

    private:
        GameObject * _target;   //what are we looking at?
        float _rotationSpeed;
        float _distace;
        float _maxRotationX;

};

#endif // Orbit_H
