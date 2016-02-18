#ifndef TRIGGERBEHAVIOUR_H
#define TRIGGERBEHAVIOUR_H

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/behaviours/DoorBehaviour.h"
#include <SFML/Graphics.hpp>
class TriggerBehaviour: public AbstractBehaviour
{
    public:
        TriggerBehaviour(GameObject * box, DoorBehaviour * doorBehaviour);
        virtual ~TriggerBehaviour();
          virtual void update( float step );
    protected:
    private:
        GameObject * _box;
        GameObject * _door;
        DoorBehaviour * _doorBehaviour;
        bool _activated;
};

#endif // TRIGGERBEHAVIOUR_H
