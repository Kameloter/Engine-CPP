#ifndef DOORBEHAVIOUR_H
#define DOORBEHAVIOUR_H

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"
#include <SFML/Graphics.hpp>

class DoorBehaviour : public AbstractBehaviour
{
    public:
        DoorBehaviour();
        virtual ~DoorBehaviour();
         virtual void update( float step );
         bool _activated;
         void InitializePositions (glm::vec3 translateUp);
    protected:
    private:
        glm::vec3 _openPos;
        glm::vec3 _closedPos;
         glm::vec3 _translateUp;
};

#endif // DOORBEHAVIOUR_H
