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
         void SetOpenPos (glm::vec3 translateUp);
		 void AddPressurePlate(GameObject * plate);
		 void InitializePositions();
    protected:
    private:
		
		std::vector<GameObject*> plates;
		bool CheckPlates();

        glm::vec3 _openPos;
        glm::vec3 _closedPos;
        glm::vec3 _translateUp;
};

#endif // DOORBEHAVIOUR_H
