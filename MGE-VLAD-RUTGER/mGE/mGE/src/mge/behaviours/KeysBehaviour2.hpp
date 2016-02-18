#ifndef KEYSBEHAVIOUR2_H
#define KEYSBEHAVIOUR2_H

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * KeysBehaviour2 allows you to move an object using the keyboard in its own local space.
 * Left right turns, forward back moves.
 */
class KeysBehaviour2 : public AbstractBehaviour
{
	public:
		KeysBehaviour2(float moveSpeed = 5, float turnSpeed = 45);
		virtual ~KeysBehaviour2();
		virtual void update( float step );

    private:
        float _moveSpeed;
        float _turnSpeed;
};

#endif // KEYSBEHAVIOUR2_H
