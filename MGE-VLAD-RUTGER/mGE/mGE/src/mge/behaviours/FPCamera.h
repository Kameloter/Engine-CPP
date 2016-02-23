#ifndef FPCAMERA_H
#define FPCAMERA_H

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"
#include <SFML/Graphics.hpp>

class FPCamera: public AbstractBehaviour
{
    public:
        FPCamera( float pMoveSpeed,float pTurnSpeed, GameObject * pPlayer, sf::Window * window);
        virtual ~FPCamera();
        virtual void update( float step );
		bool _inAction = false;
    protected:
    private:
        float _moveSpeed;
        float _turnSpeed;
        GameObject * _player;
        sf::Window * _window;
};

#endif // FPCAMERA_H
