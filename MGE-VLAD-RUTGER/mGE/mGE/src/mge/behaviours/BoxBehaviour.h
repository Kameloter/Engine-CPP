#ifndef BOXBEHAVIOUR_H
#define BOXBEHAVIOUR_H

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"
#include <SFML/Graphics.hpp>

class BoxBehaviour: public AbstractBehaviour
{
    public:
        BoxBehaviour(GameObject * player);
        virtual ~BoxBehaviour();
         virtual void update( float step );
    protected:
    private:
        GameObject * _player;
        bool _isCarried;
        bool _canPress;
};

#endif // BOXBEHAVIOUR_H
