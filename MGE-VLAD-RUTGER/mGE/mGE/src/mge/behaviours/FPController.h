#ifndef FPCONTROLLER_H
#define FPCONTROLLER_H

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"

class FPController : public AbstractBehaviour
{
    public:
        enum InputType{
            WASD, ArrowKeys
        };
        InputType _inputType;

        FPController( float pMoveSpeed,float pTurnSpeed,GameObject* pCamera, InputType pInputType);
        virtual ~FPController();
        virtual void update( float step );
    protected:
    private:
        float _moveSpeed;
        float _turnSpeed;
};

#endif // FPCONTROLLER_H
