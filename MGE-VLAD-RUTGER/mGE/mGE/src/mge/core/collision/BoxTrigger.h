#ifndef BOXTRIGGER_H
#define BOXTRIGGER_H
#include "glm.hpp"


class Collision;
class BoxTrigger 
{
    public:
        BoxTrigger(const glm::vec3 pMinBounds, const glm::vec3 pMaxBounds);
        virtual ~BoxTrigger();


		Collision* collisionInfo;

		Collision resolveCollision(BoxTrigger * colB);

        void translate(const glm::vec3 pTranslation);


        inline const glm::vec3 getMinBounds() const { return _minBounds; }
        inline const glm::vec3 getMaxBounds() const { return _maxBounds; }

    protected:
    private:
        glm::vec3 _minBounds;
        glm::vec3 _maxBounds;

};

#endif // BOXTRIGGER_H
