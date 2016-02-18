#ifndef COLLISION_H
#define COLLISION_H

class Collision
{
    public:
        Collision(const bool pCollides, const float pCollisionDistance):
            _collides(pCollides),
            _collisionDistance(pCollisionDistance) {}
      //  virtual ~Collision() {}
    inline bool getIsColliding() const { return _collides; }
    inline float getCollisionDistance() const { return _collisionDistance; }

    protected:
    private:
        const bool _collides;
        const float _collisionDistance;
};

#endif // COLLISION_H
